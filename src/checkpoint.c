#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "game.h"
#include "checkpoint.h"

#ifndef GL_CLAMP_TO_BORDER
#define GL_CLAMP_TO_BORDER 0x812F
#endif 

checkpoint initCheckpoint(float x, float y, float r, int type){
    checkpoint new_c;
    new_c.centre[0] = x;
    new_c.centre[1] = y;
    new_c.rayon= 0.5*r;
    new_c.type= type; // 0 pour les astéroides, 1 pour les étoiles, 2 pour les planètes.
    return new_c;
}

hoverPhysics initPhysics(float *x, float *y, float r){
    hoverPhysics new_c;
    new_c.centre[0] = x;
    new_c.centre[1] = y;
    new_c.rayon= 0.5*r;
    return new_c;
}

void initTextureCheckpointRock(checkpoint *check, GLuint *textureIdChekpointRock){
    
    SDL_Surface* rock;
    rock = IMG_Load("../graphics/asteroid.png");
    
    if (rock == NULL){
        fprintf(stderr, "impossible de charger l'image du rules5\n");
    }

    GLenum format=0;
    
    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, textureIdChekpointRock);
    glBindTexture(GL_TEXTURE_2D, *textureIdChekpointRock);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    
    
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    
    switch(rock->format->BytesPerPixel) {
        case 1:
            format = GL_RED;
            break;
        case 3:
            format = GL_RGB;
            break;
        case 4:
            format = GL_RGBA;
            break;
        default:
            fprintf(stderr, "Format des pixels de l'image non pris en charge\n");
            
    }
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 66, 64, 0, format, GL_UNSIGNED_BYTE, rock->pixels);
    
    glBindTexture(GL_TEXTURE_2D, 0);
    
    SDL_FreeSurface(rock);
}

void dessinCheckpointRock(checkpoint *check, int cont, GLuint *textureIdChekpointRock) {
    
    //glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, *textureIdChekpointRock);
    glColor3f(1,1,1);
    
    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();
    
    glMatrixMode(GL_MODELVIEW);
    
    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();
    glTranslatef(0.5,0.5,0.0);
    glRotatef(cont, 0, 0, 1);
    glTranslatef(-0.5,-0.5,0.0);
    glMatrixMode(GL_MODELVIEW);
    
    glPushMatrix();
    
    glBegin(GL_QUADS);
 
    glTexCoord2f(0,1);
    glVertex2f(check->centre[0]-10, check->centre[1]+10);
    
    glTexCoord2f(0,0);
    glVertex2f(check->centre[0]-10, check->centre[1]-10);
    
    glTexCoord2f(1,0);
    glVertex2f(check->centre[0]+10, check->centre[1]-10);
    
    glTexCoord2f(1,1);
    glVertex2f(check->centre[0]+10, check->centre[1]+10);
    
    glEnd();
    glPopMatrix();
      
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
}

void initTextureCheckpointStar(checkpoint *check, GLuint *textureIdChekpointStar){

    SDL_Surface* star;
    star = IMG_Load("../graphics/fuel-stars.png");
    
    if (star == NULL){
        fprintf(stderr, "impossible de charger l'image du rules5\n");
    }

    GLenum format=0;
    
    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, textureIdChekpointStar);
    glBindTexture(GL_TEXTURE_2D, *textureIdChekpointStar);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    
    switch(star->format->BytesPerPixel) {
        case 1:
            format = GL_RED;
            break;
        case 3:
            format = GL_RGB;
            break;
        case 4:
            format = GL_RGBA;
            break;
        default:
            fprintf(stderr, "Format des pixels de l'image non pris en charge\n");
            
    }
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 196, 192, 0, format, GL_UNSIGNED_BYTE, star->pixels);
    
    glBindTexture(GL_TEXTURE_2D, 0);
    
    SDL_FreeSurface(star);

}
    
void dessinCheckpointStar(checkpoint *check, int cont, GLuint *textureIdChekpointStar) {

    //glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, *textureIdChekpointStar);
    glColor3f(1,1,1);
    
    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();
    
    glMatrixMode(GL_MODELVIEW);
    
    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();
    glTranslatef(0.5,0.5,0.0);
    glRotatef(cont, 0, 0, 1);
    glTranslatef(-0.5,-0.5,0.0);
    glMatrixMode(GL_MODELVIEW);
    
    glPushMatrix();
    
    glBegin(GL_QUADS);

    glTexCoord2f(0,1);
    glVertex2f(check->centre[0]-10, check->centre[1]+10);
    
    glTexCoord2f(0,0);
    glVertex2f(check->centre[0]-10, check->centre[1]-10);
    
    glTexCoord2f(1,0);
    glVertex2f(check->centre[0]+10, check->centre[1]-10);
    
    glTexCoord2f(1,1);
    glVertex2f(check->centre[0]+10, check->centre[1]+10);
    
    glEnd();
    glPopMatrix();
    
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
        
}

void initTextureCheckpointPlanet(checkpoint *check, GLuint *textureIdChekpointPlanet){
    
    SDL_Surface* planet;
    planet = IMG_Load("../graphics/planet.png");

    GLenum format=0;
    
    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, textureIdChekpointPlanet);
    glBindTexture(GL_TEXTURE_2D, *textureIdChekpointPlanet);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    
    
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    
    switch(planet->format->BytesPerPixel) {
        case 1:
            format = GL_RED;
            break;
        case 3:
            format = GL_RGB;
            break;
        case 4:
            format = GL_RGBA;
            break;
        default:
            fprintf(stderr, "Format des pixels de l'image non pris en charge\n");
            
    }
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, planet->w, planet->h, 0, format, GL_UNSIGNED_BYTE, planet->pixels);
    
    glBindTexture(GL_TEXTURE_2D, 0);
    
    SDL_FreeSurface(planet);

}

void dessinCheckpointPlanet(checkpoint *check, int cont, GLuint *textureIdChekpointPlanet) {

    //glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, *textureIdChekpointPlanet);
    glColor3f(1,1,1);    
    
    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);
    
    glPushMatrix();
    
        glBegin(GL_QUADS);

        
        glTexCoord2f(0,1);
        glVertex2f(check->centre[0]-30, check->centre[1]+30);
        
        glTexCoord2f(0,0);
        glVertex2f(check->centre[0]-30, check->centre[1]-30);
        
        glTexCoord2f(1,0);
        glVertex2f(check->centre[0]+30, check->centre[1]-30);
        
        glTexCoord2f(1,1);
        glVertex2f(check->centre[0]+30, check->centre[1]+30);
        
        
        glEnd();
    glPopMatrix();
    
    
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);

}
    

