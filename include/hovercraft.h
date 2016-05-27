#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "checkpoint.h"

#ifndef HOVERCRAFT
#define HOVERCRAFT

typedef struct{
    float moteur;
    float couple;
    float posX;
    float posY;
    float vitX;
    float vitY;
    float angle;
    float omega;
    float frottement;
    float cplfrott;
    float fuel;
    hoverPhysics centre;
}hovercraft;

hovercraft initHovercraft(float x, float y, float vitx, float vity, float angle, float omega, float frottement, float cplfrott, float moteur, float couple,float fuel);
void deplacementHovercraft(hovercraft *hover, int *trigger, int *triggerD);
int colisionHovercraftCheckpoint(checkpoint check, hovercraft *hover, int *etat1);
void initTextureHovercraft(GLuint *textureIdHovercraft);
void drawHovercraft(hovercraft *hover, GLuint *textureIdHovercraft);

#endif 
