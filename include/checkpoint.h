#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>

#ifndef CHECKPOINT
#define CHECKPOINT

typedef struct checkpoint{
    float centre[2];
    float rayon;
    int type;
}checkpoint;

typedef struct{
    float *centre[2];
    float rayon;
}hoverPhysics;

checkpoint initCheckpoint(float x, float y, float r, int type);
hoverPhysics initPhysics(float *x, float *y, float r);
void initTextureCheckpointRock(checkpoint *check, GLuint *textureIdChekpointRock);
void dessinCheckpointRock(checkpoint *check, int cont, GLuint *textureIdChekpointRock);
void initTextureCheckpointStar(checkpoint *check, GLuint *textureIdChekpointStar);
void dessinCheckpointStar(checkpoint *check, int cont, GLuint *textureIdChekpointStar);
void initTextureCheckpointPlanet(checkpoint *check, GLuint *textureIdChekpointPlanet);
void dessinCheckpointPlanet(checkpoint *check, int cont, GLuint *textureIdChekpointPlanet);

#endif 
