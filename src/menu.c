#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#include "menu.h"
#include "game.h"
#include "hovercraft.h"

#ifndef GL_CLAMP_TO_BORDER
#define GL_CLAMP_TO_BORDER 0x812F
#endif 

int cas( int x, int y){
    if (90 < x && x< 370 && 531 < y && y< 610)  {
        //printf("ça joue");
        return 1;
    }
    else if (910 < x && x< 1190 && 530 < y && y < 609) {
        //printf("ça quitte");
        return 2;
    }
    else if (1180 < x && x< 1250 && 15 < y && y< 75){
        //menu
        return 0;
    }
    else if (500 < x && x< 780 && 530 < y && y< 610){
        //menu2
        return 3;
    }
    else
        return 0;
}



void boutonMenu( int x, int y, int xdec, int ydec){
    
    
    if (90 < x && x< 370 && 531 < y && y< 610) {
        glPushMatrix();
        glTranslatef(-125.5 + xdec,-64.5 + ydec,0.0);
        glScalef(83.5,24.5,0.0);
        glColor3f(.2,0.2,1.0);
        glBegin(GL_LINE_LOOP);
        glVertex2f(-0.5,-0.5);
        glVertex2f(-0.5,0.5);
        glVertex2f(0.5,0.5);
        glVertex2f(0.5,-0.5);
        glEnd();
        glPopMatrix();
    }
    else if (910 < x && x< 1190 && 530 < y && y < 609) {
        glPushMatrix();
        glTranslatef(125.5 + xdec,-64.5 + ydec,0.0);
        glScalef(83.5,24.5,0.0);
        glColor3f(.2,0.2,1.0);
        glBegin(GL_LINE_LOOP);
        glVertex2f(-0.5,-0.5);
        glVertex2f(-0.5,0.5);
        glVertex2f(0.5,0.5);
        glVertex2f(0.5,-0.5);
        glEnd();
        glPopMatrix();
        
    }
    else if (500 < x && x< 780 && 530 < y && y< 610) {
        glPushMatrix();
        glTranslatef(0 + xdec,-64.5 + ydec,0.0);
        glScalef(83.5,24.5,0.0);
        glColor3f(.2,0.2,1.0);
        glBegin(GL_LINE_LOOP);
        glVertex2f(-0.5,-0.5);
        glVertex2f(-0.5,0.5);
        glVertex2f(0.5,0.5);
        glVertex2f(0.5,-0.5);
        glEnd();
        glPopMatrix();
        
    }
    
    
}

void initTextureMenu(GLuint *textureIdMenu) {

    SDL_Surface* menu;
    menu = IMG_Load("../graphics/menu.png");
    if (menu == NULL){
        fprintf(stderr, "impossible de charger l'image du rules1\n");
    }
    
    GLenum format = 0;
    
    glGenTextures(1, textureIdMenu);
    glBindTexture(GL_TEXTURE_2D, *textureIdMenu);
    
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    
    switch(menu->format->BytesPerPixel) {
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
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1281, 720, 0, format, GL_UNSIGNED_BYTE, menu->pixels);
    
    glBindTexture(GL_TEXTURE_2D, 0);
    
    SDL_FreeSurface(menu);

}

void afficherMenu(hovercraft *hover, GLuint *textureIdMenu){
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, *textureIdMenu);
    
    glColor3f(1,1,1);
    
    
    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);
    
    glBegin(GL_QUADS);
    glPushMatrix() ;
    
    glTexCoord2f(0,1);
    glVertex2f(-200 + hover->posX, -112.5 + hover->posY);
    
    glTexCoord2f(0,0);
    glVertex2f(-200 + hover->posX, 112.5 + hover->posY);
    
    glTexCoord2f(1,0);
    glVertex2f(200 + hover->posX, 112.5 + hover->posY);
    
    glTexCoord2f(1,1);
    glVertex2f(200 + hover->posX, -112.5 + hover->posY);

    glPopMatrix();
    glEnd();
    
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
    
}

void initTextureMenu2(GLuint *textureIdMenu2){
    SDL_Surface* image2;
    image2 = IMG_Load("../graphics/menu2.png");
    if (image2 == NULL){
        fprintf(stderr, "impossible de charger l'image du rules2\n");
    }
    
    GLenum format = 0;
    
    glGenTextures(1, textureIdMenu2);
    glBindTexture(GL_TEXTURE_2D, *textureIdMenu2);
    
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    
    switch(image2->format->BytesPerPixel) {
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
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1281, 720, 0, format, GL_UNSIGNED_BYTE, image2->pixels);
    
    glBindTexture(GL_TEXTURE_2D, 1);
    
    SDL_FreeSurface(image2);

}

void afficherMenu2(hovercraft *hover, GLuint *textureIdMenu2){
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, *textureIdMenu2);
    
    glColor3f(1,1,1);
    
    glBegin(GL_QUADS);
    
    glTexCoord2f(0,1);
    glVertex2f(-198 + hover->posX, -110.5 + hover->posY);
    
    glTexCoord2f(0,0);
    glVertex2f(-198 + hover->posX, 110.5 + hover->posY);
    
    glTexCoord2f(1,0);
    glVertex2f(198 + hover->posX, 110.5 + hover->posY);
    
    glTexCoord2f(1,1);
    glVertex2f(198 + hover->posX, -110.5 + hover->posY);
    
    glEnd();
    
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
    
}

void initTextureMenuWin(GLuint *textureIdMenuWin){
    SDL_Surface* Win;
    Win = IMG_Load("../graphics/youwin.png");
    if (Win == NULL){
        fprintf(stderr, "impossible de charger l'image du rules2\n");
    }
    
    GLenum format = 0;
    
    glGenTextures(1, textureIdMenuWin);
    glBindTexture(GL_TEXTURE_2D, *textureIdMenuWin);
    
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    
    switch(Win->format->BytesPerPixel) {
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
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1281, 720, 0, format, GL_UNSIGNED_BYTE, Win->pixels);
    
    glBindTexture(GL_TEXTURE_2D, 1);
    
    SDL_FreeSurface(Win);

}

void afficherMenuWin(hovercraft *hover, GLuint *textureIdMenuWin){
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, *textureIdMenuWin);
    
    glColor3f(1,1,1);
    
    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);
    
    glBegin(GL_QUADS);
    glPushMatrix() ;
    
    glTexCoord2f(0,1);
    glVertex2f(-200 + hover->posX, -112.5 + hover->posY);
    
    glTexCoord2f(0,0);
    glVertex2f(-200 + hover->posX, 112.5 + hover->posY);
    
    glTexCoord2f(1,0);
    glVertex2f(200 + hover->posX, 112.5 + hover->posY);
    
    glTexCoord2f(1,1);
    glVertex2f(200 + hover->posX, -112.5 + hover->posY);
    
    glEnd();
    
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
    
}

void initTextureMenuLose(GLuint *textureIdMenuLose){
    SDL_Surface* Lose;
    Lose = IMG_Load("../graphics/youlose.png");
    if (Lose == NULL){
        fprintf(stderr, "impossible de charger l'image du rules2\n");
    }
    
    GLenum format = 0;
    
    glGenTextures(1, textureIdMenuLose);
    glBindTexture(GL_TEXTURE_2D, *textureIdMenuLose);
    
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    
    switch(Lose->format->BytesPerPixel) {
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
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1281, 720, 0, format, GL_UNSIGNED_BYTE, Lose->pixels);
    
    glBindTexture(GL_TEXTURE_2D, 1);
    
    SDL_FreeSurface(Lose);

}

void afficherMenuLose(hovercraft *hover, GLuint *textureIdMenuLose){
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, *textureIdMenuLose);
    
    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);
    
    glBegin(GL_QUADS);
    glPushMatrix() ;
    
    glTexCoord2f(0,1);
    glVertex2f(-200 + hover->posX, -112.5 + hover->posY);
    
    glTexCoord2f(0,0);
    glVertex2f(-200 + hover->posX, 112.5 + hover->posY);
    
    glTexCoord2f(1,0);
    glVertex2f(200 + hover->posX, 112.5 + hover->posY);
    
    glTexCoord2f(1,1);
    glVertex2f(200 + hover->posX, -112.5 + hover->posY);
    
    glEnd();
    
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
    
}

void initTextureBackground(GLuint *textureIdBackground){
    SDL_Surface* image2;
    image2 = IMG_Load("../graphics/bg2.png");
    if (image2 == NULL){
        fprintf(stderr, "impossible de charger l'image du rules3\n");
    }

    GLenum format = 0;
    
    glGenTextures(1, textureIdBackground);
    glBindTexture(GL_TEXTURE_2D, *textureIdBackground);
    
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    
    switch(image2->format->BytesPerPixel) {
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
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 448, 448, 0, format, GL_UNSIGNED_BYTE, image2->pixels);
    
    glBindTexture(GL_TEXTURE_2D, 0);
    
    SDL_FreeSurface(image2);
}

void background(int x1, int x2, int y1, int y2, GLuint *textureIdBackground){
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, *textureIdBackground);
    
    glColor3f(1,1,1);
    
    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();
    
    glMatrixMode(GL_MODELVIEW);
    
    glBegin(GL_QUADS);
    
    glTexCoord2f(0,12);
    glVertex2f(4*x1 , 4*x1);
    
    glTexCoord2f(0,0);
    glVertex2f(4*x1, 4*x2);
    
    glTexCoord2f(12,0);
    glVertex2f(4*x2, 4*x2);
    
    glTexCoord2f(12,12);
    glVertex2f(4*x2, 4*x1);
    
    glEnd();
    
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
    
}