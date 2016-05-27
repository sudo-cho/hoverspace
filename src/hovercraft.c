#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "game.h"
#include "hovercraft.h"

#ifndef M_PI
#define M_PI  3.14159265358979323846
#endif

#ifndef GL_CLAMP_TO_BORDER
#define GL_CLAMP_TO_BORDER 0x812F
#endif 

hovercraft initHovercraft(float x, float y, float vitx, float vity, float angle, float omega, float frottement, float cplfrott, float moteur, float couple,float fuel){
    hovercraft new_hovercraft;
    new_hovercraft.posX = x;
    new_hovercraft.posY = y;
    new_hovercraft.vitX = vitx;
    new_hovercraft.vitY = vity;
    new_hovercraft.angle = angle;
    new_hovercraft.omega = omega;
    new_hovercraft.frottement = frottement;
    new_hovercraft.cplfrott = cplfrott;
    new_hovercraft.moteur = moteur;
    new_hovercraft.couple = couple;
    new_hovercraft.fuel = fuel;
    return new_hovercraft;
}

void deplacementHovercraft(hovercraft *hover, int *trigger, int *triggerD){
    float ax, ay, omegadt;
    if(*trigger == 0)
        hover->moteur = 0;
    if(*triggerD == 0)
        hover->couple = 0;
    if(*triggerD == 1)
        hover->couple += 0.01;
    if(*triggerD == 2)
        hover->couple -= 0.01;
    if(*trigger == 3)
        hover->moteur -= 0.001;
    if(*trigger == 4)
        hover->moteur += 0.005;
    
    //angulaire
    //hover->angle = hover->angle + hover->couple;
    ax = hover->moteur*sin(M_PI*(hover->angle)/180);
    ay = hover->moteur*cos(M_PI*(hover->angle)/180);
    
    omegadt = hover->couple;
    
    //horizontale
    hover->vitX += -(hover->frottement)*(hover->vitX) + ax;
    hover->posX = hover->posX + hover->vitX;
    //printf("%f", hover->moteur);
    //verticale
    hover->vitY +=  -(hover->frottement)*(hover->vitY) + ay;
    hover->posY = hover->posY + hover->vitY;
    
    hover->omega = hover->omega -(hover->cplfrott)*(hover->omega) + omegadt;
    hover->angle = hover->omega + hover->angle;

}

int colisionHovercraftCheckpoint(checkpoint check, hovercraft *hover, int *etat1) {
    
    float distanceCheckHover = ((*hover->centre.centre[0] - check.centre[0]) * (*hover->centre.centre[0] - check.centre[0]) + (*hover->centre.centre[1] - check.centre[1]) * (*hover->centre.centre[1] - check.centre[1]));
    
    if(  distanceCheckHover < ((check.rayon)+(hover->centre.rayon))*((check.rayon)+(hover->centre.rayon))   ){
        if (check.type == 0){
            hover->vitX = -hover->vitX;
            hover->vitY = -hover->vitY;
            hover->fuel -= 5;
            return 1;
        }
            else if (check.type == 1){
            hover->moteur += 0.05;
            hover->fuel += 10;
            check.type = 3;
            return 2;
        }
            else{
                *etat1 = 4;
                printf("Vous avez gagné\n");
                return 4;
            }
    }
    return 0;
    

}

void initTextureHovercraft(GLuint *textureIdHovercraft){
    SDL_Surface* ship;
    ship = IMG_Load("../graphics/spaceship.png");
    if (ship == NULL){
        fprintf(stderr, "impossible de charger l'image du ruleship\n");
    }

    GLenum format = 0;
    
    glGenTextures(1, textureIdHovercraft);
    glBindTexture(GL_TEXTURE_2D, *textureIdHovercraft);
    
    
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    
    switch(ship->format->BytesPerPixel) {
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
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 709, 772, 0, format, GL_UNSIGNED_BYTE, ship->pixels);
    
    glBindTexture(GL_TEXTURE_2D, 0);
    
    SDL_FreeSurface(ship);

}

void drawHovercraft(hovercraft *hover, GLuint *textureIdHovercraft){
  
    glEnable(GL_TEXTURE_2D);
    //glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D, *textureIdHovercraft);
    glColor3f(1,1,1);
    
    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();
    
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
        glMatrixMode(GL_TEXTURE);
        glLoadIdentity();
        glTranslatef(0.5,0.5,0.0);
        glRotatef(-hover->angle, 0, 0, 1);
        glTranslatef(-0.5,-0.5,0.0);
        glMatrixMode(GL_MODELVIEW);
        
        
        glBegin(GL_QUADS);
            glTexCoord2f(0,1);
            glVertex2f(-9+hover->posX, -11+hover->posY);
            
            glTexCoord2f(0,0);
            glVertex2f(-9+hover->posX, 11+hover->posY);
            
            glTexCoord2f(1,0);
            glVertex2f(9+hover->posX, 11+hover->posY);
            
            glTexCoord2f(1,1);
            glVertex2f(9+hover->posX, -11+hover->posY);
        glEnd();
    glPopMatrix();


    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
    

}

