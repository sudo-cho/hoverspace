#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "game.h"
#include "menu.h"
#include "hovercraft.h"
#include "checkpoint.h"


void chargerMap(int bounds[4]) {

    FILE* map = NULL;
    map = fopen("map.txt", "r+");

    if (map != NULL){
        fscanf(map, "bounds (%d,%d,%d,%d)", &bounds[0], &bounds[1], &bounds[2], &bounds[3]);
        fclose(map); 
    }

}

void initGame(
        int *xmous, int *ymous, int *xmousCont, int *ymousCont, int *etat1, int *winCond, int *triggerD, 
        int *trigger, int *windowWidth, int *windowHeight, checkpoint *check, hovercraft *hover, int *deathstar1, int *deathstar2, int *deathstar3, int *deathstar4,
        int *cont, int *camZoom, GLuint *textureIdHover, GLuint *textureIdCheckpointRock, GLuint *textureIdCheckpointStar, GLuint *textureIdCheckpointPlanet, 
        GLuint *textureIdMenu, GLuint *textureIdMenu2, GLuint *textureIdBackground, GLuint *textureIdMenuWin, GLuint *textureIdMenuLose
     ) {
  
    /* Dimensions de la fenêtre */
    *windowWidth  = 1280;
    *windowHeight = 720;
    
    /* Triggers */
    *trigger  = 0;
    *triggerD = 0;
    
    /* hovercraft */
    *hover = initHovercraft(0,0, 0, 0, 0, 0, 0.05, 0.1, 0, 0, 200);
    hover->centre = initPhysics(&hover->posX, &hover->posY, 30);
    
    /* checkpoint */
    *check = initCheckpoint(-50, 100, 20, 0);

    /*souris */
    *xmous = 1233;
    *ymous = 35;
    
    *xmousCont = 0;
    *ymousCont = 0;

    *etat1 = 0;
    *winCond = 0;

    *deathstar1 = 1;
    *deathstar2 = 1;
    *deathstar3 = 1;
    *deathstar4 = 1;

    *cont = 0;
    *camZoom = 2.1;

    initTextureHovercraft(textureIdHover);
    initTextureCheckpointRock(check, textureIdCheckpointRock);
    initTextureCheckpointStar(check, textureIdCheckpointStar);
    initTextureCheckpointPlanet(check, textureIdCheckpointPlanet);
    initTextureMenu(textureIdMenu);
    initTextureMenu2(textureIdMenu2);
    initTextureBackground(textureIdBackground);
    initTextureMenuWin(textureIdMenuWin);
    initTextureMenuLose(textureIdMenuLose);
}

