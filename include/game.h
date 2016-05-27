#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "checkpoint.h"
#include "hovercraft.h"

#ifndef GAME
#define GAME

void chargerMap();
void initGame(
        int *xmous, int *ymous, int *xmousCont, int *ymousCont, int *etat1, int *winCond, int *triggerD, 
        int *trigger, int *windowWidth, int *windowHeight, checkpoint *check, hovercraft *hover, int *deathstar1, int *deathstar2, int *deathstar3, int *deathstar4,
        int *cont, int *camZoom, GLuint *textureIdHover, GLuint *textureIdCheckpointRock, GLuint *textureIdCheckpointStar, GLuint *textureIdCheckpointPlanet, 
        GLuint *textureIdMenu, GLuint *textureIdMenu2, GLuint *textureIdBackground, GLuint *textureIdMenuWin, GLuint *textureIdMenuLose
     );
  

#endif 

