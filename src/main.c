//
//  main.c
//  Hovercraft
//
//  Created by Arthur Ducoux and Lucas Dussouchaud


#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <time.h>

#include "game.h"
#include "menu.h"
#include "draw.h"

//#ifndef GL_CLAMP_TO_BORDER
//#define GL_CLAMP_TO_BORDER 0x812F
//#endif 

/* ------------------------ CONSTANTES ---------------- */
static const unsigned int BIT_PER_PIXEL = 32;

static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

int TIMER = 0;

/* ------------------------ CONSTANTES ---------------- */




/* ------------------------ GL OPTIONS ---------------- */
void reshape(unsigned int windowWidth, unsigned int windowHeight) {
    glViewport(0, 0, windowWidth, windowHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-200.0, 200.0, -200.0*(windowHeight/(float)(windowWidth)), 200.0*(windowHeight/(float)(windowWidth)));
    gluPerspective(50, 1., 1., 100.);
    glMatrixMode(GL_MODELVIEW);
}

void setVideoMode(unsigned int windowWidth, unsigned int windowHeight) {
    if(NULL == SDL_SetVideoMode(windowWidth, windowHeight, BIT_PER_PIXEL, SDL_OPENGL | SDL_RESIZABLE )) {
        fprintf(stderr, "Impossible d'ouvrir la fenetre. Fin du programme.\n");
        exit(EXIT_FAILURE);
    }
    
}
/* ------------------------ GL OPTIONS ---------------- */

int main(int argc, char* args[]) {
    
    /* Initialisation de la SDL */
    if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
        return EXIT_FAILURE;
    }
    setVideoMode(1280, 720);


    /* données de la map */
    int bounds[4] = {0,1,2,3};
    chargerMap(bounds);

    int x1 = -2000;
    int x2 = 2000;
    int y1 = -1125;
    int y2 = 1125;

    /* Variables */
    hovercraft hover;
    checkpoint check;
    
    GLuint textureIdHover, textureIdCheckpointRock, textureIdCheckpointStar, textureIdCheckpointPlanet, textureIdMenu, textureIdMenu2, textureIdBackground, textureIdMenuWin, textureIdMenuLose;

    int xmous,ymous,xmousCont,ymousCont,etat1,
    triggerD,trigger,windowWidth,windowHeight,
    winCond,deathstar1,deathstar2,deathstar3,deathstar4,cont,camZoom;

    initGame(
        &xmous, &ymous, &xmousCont, &ymousCont, &etat1, &winCond, &triggerD, 
        &trigger, &windowWidth, &windowHeight, &check, &hover, &deathstar1, &deathstar2, &deathstar3, &deathstar4,
        &cont, &camZoom, &textureIdHover, &textureIdCheckpointRock, &textureIdCheckpointStar, &textureIdCheckpointPlanet, &textureIdMenu, &textureIdMenu2, &textureIdBackground, &textureIdMenuWin, &textureIdMenuLose
    );
    
    /* checkpoint */
    srand(time(NULL));

    printf("%d\n",x1);
    
    int xrand1 = rand() % (x2-x1) - x2;
    int xrand2 = rand() % (x2-x1) - x2;
    int xrand3 = rand() % (x2-x1) - x2;
    int xrand4 = rand() % (x2-x1) - x2;
    int xrand5 = rand() % (x2-x1) - x2;
    int xrand6 = rand() % (x2-x1) - x2;
    int xrand7 = rand() % (x2-x1) - x2;
    int xrand8 = rand() % (x2-x1) - x2;
    int xrand9 = rand() % (x2-x1) - x2;
    int xrand10 = rand() % (x2-x1) - x2;
    
    int yrand1 = rand() % (y2-y1) - y2;
    int yrand2 = rand() % (y2-y1) - y2;
    int yrand3 = rand() % (y2-y1) - y2;
    int yrand4 = rand() % (y2-y1) - y2;
    int yrand5 = rand() % (y2-y1) - y2;
    int yrand6 = rand() % (y2-y1) - y2;
    int yrand7 = rand() % (y2-y1) - y2;
    int yrand8 = rand() % (y2-y1) - y2;
    int yrand9 = rand() % (y2-y1) - y2;
    int yrand10 = rand() % (y2-y1) - y2;
    
    checkpoint star1 = initCheckpoint(xrand1, yrand1, 20, 1);
    checkpoint star2 = initCheckpoint(xrand2, yrand2, 20, 1);
    checkpoint star3 = initCheckpoint(xrand3, yrand3, 20, 1);
    checkpoint star4 = initCheckpoint(xrand4, yrand4, 20, 1);
    
    checkpoint rock1 = initCheckpoint(xrand6, yrand6, 20, 0);
    checkpoint rock2 = initCheckpoint(xrand7, yrand7, 20, 0);
    checkpoint rock3 = initCheckpoint(xrand8, yrand8, 20, 0);
    checkpoint rock4 = initCheckpoint(xrand9, yrand9, 20, 0);
    checkpoint rock5 = initCheckpoint(xrand10, yrand10, 20, 0);
    
    checkpoint planet = initCheckpoint(xrand5, yrand5, 60, 2);

    /*GLuint scene = 0;
    scene = glGenLists(1);

    glNewList(scene, GL_COMPILE);
        drawHovercraft(&hover, textureIdHover);
        background(x1,x2,y1,y2, textureIdBackground);
        dessinCheckpoint(&rock1, cont);
        dessinCheckpoint(&rock2, cont);
        dessinCheckpoint(&rock3, cont);
        dessinCheckpoint(&rock4, cont);
        dessinCheckpoint(&rock5, cont);
        dessinCheckpoint(&planet, cont);
    glEndList();
    */
    
    SDL_WM_SetCaption("Hoverspace", NULL);

    gluLookAt(hover.posX, hover.posY, camZoom,hover.posX, hover.posY, 1.,0., 1., 0.);

    reshape(windowWidth, windowHeight);
    
    /* Boucle d'affichage */
    int loop = 1;
    while(loop) {

        /* Récupération du temps au début de la boucle */
        Uint32 startTime = SDL_GetTicks();
 
        if (etat1 == 2){
            loop = 0;
        }
        
        else if(etat1 == 0) {
            
            glLoadIdentity();
            gluLookAt(hover.posX, hover.posY, camZoom,hover.posX, hover.posY, 1.,0., 1., 0.);

            TIMER = 0;
            afficherMenu(&hover, &textureIdMenu);
            boutonMenu(xmousCont, ymousCont,hover.posX, hover.posY);
            etat1 = cas(xmous, ymous);
            
        }
            
        else if (etat1 == 1) {

            if(hover.fuel < 0.0) {

                etat1 = 5;
            }

            printf("%f\n", hover.fuel);

            hover.fuel -= 0.1;
            
            
            /* camera */
            glLoadIdentity();
            gluLookAt(hover.posX, hover.posY, camZoom, hover.posX, hover.posY, 1.,0., 1., 0.);
            

/*
            glPushMatrix();
            glTranslatef(0 + hover.posX, 0+ hover.posY,0.0);
            glScalef(5.0,hover.fuel,0.0);
            dessinCarreRond();
            glPopMatrix();*/
    
            
            /* Bornes écran */
            if(hover.posX > x2){
             hover.posX = x2;
            }
             else if(hover.posX < x1){
             hover.posX = x1;
            }
             
             if(hover.posY > y2){
             hover.posY = y2;
            }
             else if(hover.posY < y1){
             hover.posY = y1;
            }
            
            /* on clear le buffer */
            glClear(GL_COLOR_BUFFER_BIT);
            
            
            background(x1,x2,y1,y2,&textureIdBackground);
            
            deplacementHovercraft(&hover,&trigger,&triggerD);
            
            
            /* Scène principal du jeu */
            cont++;

            //glCallList(scene);


            drawHovercraft(&hover, &textureIdHover);
            
            
            dessinCheckpointRock(&rock1, cont, &textureIdCheckpointRock);
            dessinCheckpointRock(&rock2, cont, &textureIdCheckpointRock);
            dessinCheckpointRock(&rock3, cont, &textureIdCheckpointRock);
            dessinCheckpointRock(&rock4, cont, &textureIdCheckpointRock);
            dessinCheckpointRock(&rock5, cont, &textureIdCheckpointRock);
            
            dessinCheckpointPlanet(&planet, cont, &textureIdCheckpointPlanet);
            
            if (colisionHovercraftCheckpoint(star1, &hover, &etat1)!= 2 && deathstar1 == 1) {
                dessinCheckpointStar(&star1, cont, &textureIdCheckpointStar);
            }else
                deathstar1 = 0;
            
            if (colisionHovercraftCheckpoint(star2, &hover, &etat1)!= 2 && deathstar2 == 1) {
                dessinCheckpointStar(&star2, cont, &textureIdCheckpointStar);
            }else
                deathstar2 = 0;
            
            if (colisionHovercraftCheckpoint(star3, &hover, &etat1)!= 2 && deathstar3 == 1) {
                dessinCheckpointStar(&star3, cont, &textureIdCheckpointStar);
            }else
                deathstar3 = 0;
            
            if (colisionHovercraftCheckpoint(star4, &hover, &etat1)!= 2 && deathstar4 == 1) {
                dessinCheckpointStar(&star4, cont, &textureIdCheckpointStar);
            }else
                deathstar4 = 0;

            
            
            /* colision */
            colisionHovercraftCheckpoint(rock1, &hover, &etat1);
            colisionHovercraftCheckpoint(rock2, &hover, &etat1);
            colisionHovercraftCheckpoint(rock3, &hover, &etat1);
            colisionHovercraftCheckpoint(rock4, &hover, &etat1);
            colisionHovercraftCheckpoint(rock5, &hover, &etat1);
            colisionHovercraftCheckpoint(planet, &hover, &etat1);

        }
        
        
        else if (etat1 == 3){
            afficherMenu2(&hover, &textureIdMenu2);
            
        }



        else if (etat1 == 4){
            camZoom = 2.1;
            afficherMenuWin(&hover, &textureIdMenuWin);

            if( TIMER == 160) {
                initGame(
                    &xmous, &ymous, &xmousCont, &ymousCont, &etat1, &winCond, &triggerD, 
                    &trigger, &windowWidth, &windowHeight, &check, &hover, &deathstar1, &deathstar2, &deathstar3, &deathstar4,
                    &cont, &camZoom, &textureIdHover, &textureIdCheckpointRock, &textureIdCheckpointStar, &textureIdCheckpointPlanet, &textureIdMenu, &textureIdMenu2, &textureIdBackground, &textureIdMenuWin, &textureIdMenuLose
                );

                xrand1 = rand() % (x2-x1) - x2;
                xrand2 = rand() % (x2-x1) - x2;
                xrand3 = rand() % (x2-x1) - x2;
                xrand4 = rand() % (x2-x1) - x2;
                xrand5 = rand() % (x2-x1) - x2;
                xrand6 = rand() % (x2-x1) - x2;
                xrand7 = rand() % (x2-x1) - x2;
                xrand8 = rand() % (x2-x1) - x2;
                xrand9 = rand() % (x2-x1) - x2;
                xrand10 = rand() % (x2-x1) - x2;
                
                yrand1 = rand() % (y2-y1) - y2;
                yrand2 = rand() % (y2-y1) - y2;
                yrand3 = rand() % (y2-y1) - y2;
                yrand4 = rand() % (y2-y1) - y2;
                yrand5 = rand() % (y2-y1) - y2;
                yrand6 = rand() % (y2-y1) - y2;
                yrand7 = rand() % (y2-y1) - y2;
                yrand8 = rand() % (y2-y1) - y2;
                yrand9 = rand() % (y2-y1) - y2;
                yrand10 = rand() % (y2-y1) - y2;
                
                star1 = initCheckpoint(xrand1, yrand1, 20, 1);
                star2 = initCheckpoint(xrand2, yrand2, 20, 1);
                star3 = initCheckpoint(xrand3, yrand3, 20, 1);
                star4 = initCheckpoint(xrand4, yrand4, 20, 1);
                
                rock1 = initCheckpoint(xrand6, yrand6, 20, 0);
                rock2 = initCheckpoint(xrand7, yrand7, 20, 0);
                rock3 = initCheckpoint(xrand8, yrand8, 20, 0);
                rock4 = initCheckpoint(xrand9, yrand9, 20, 0);
                rock5 = initCheckpoint(xrand10, yrand10, 20, 0);
                planet = initCheckpoint(xrand5, yrand5, 60, 2);
            }
            TIMER++;
            
        }

        else if (etat1 == 5){
            camZoom = 2.1;
            afficherMenuLose(&hover, &textureIdMenuLose);
            if( TIMER == 160) {
                initGame(
                    &xmous, &ymous, &xmousCont, &ymousCont, &etat1, &winCond, &triggerD, 
                    &trigger, &windowWidth, &windowHeight, &check, &hover, &deathstar1, &deathstar2, &deathstar3, &deathstar4,
                    &cont, &camZoom, &textureIdHover, &textureIdCheckpointRock, &textureIdCheckpointStar, &textureIdCheckpointPlanet, &textureIdMenu, &textureIdMenu2, &textureIdBackground, &textureIdMenuWin, &textureIdMenuLose
                );

                xrand1 = rand() % (x2-x1) - x2;
                xrand2 = rand() % (x2-x1) - x2;
                xrand3 = rand() % (x2-x1) - x2;
                xrand4 = rand() % (x2-x1) - x2;
                xrand5 = rand() % (x2-x1) - x2;
                xrand6 = rand() % (x2-x1) - x2;
                xrand7 = rand() % (x2-x1) - x2;
                xrand8 = rand() % (x2-x1) - x2;
                xrand9 = rand() % (x2-x1) - x2;
                xrand10 = rand() % (x2-x1) - x2;
                
                yrand1 = rand() % (y2-y1) - y2;
                yrand2 = rand() % (y2-y1) - y2;
                yrand3 = rand() % (y2-y1) - y2;
                yrand4 = rand() % (y2-y1) - y2;
                yrand5 = rand() % (y2-y1) - y2;
                yrand6 = rand() % (y2-y1) - y2;
                yrand7 = rand() % (y2-y1) - y2;
                yrand8 = rand() % (y2-y1) - y2;
                yrand9 = rand() % (y2-y1) - y2;
                yrand10 = rand() % (y2-y1) - y2;
                
                star1 = initCheckpoint(xrand1, yrand1, 20, 1);
                star2 = initCheckpoint(xrand2, yrand2, 20, 1);
                star3 = initCheckpoint(xrand3, yrand3, 20, 1);
                star4 = initCheckpoint(xrand4, yrand4, 20, 1);
                
                rock1 = initCheckpoint(xrand6, yrand6, 20, 0);
                rock2 = initCheckpoint(xrand7, yrand7, 20, 0);
                rock3 = initCheckpoint(xrand8, yrand8, 20, 0);
                rock4 = initCheckpoint(xrand9, yrand9, 20, 0);
                rock5 = initCheckpoint(xrand10, yrand10, 20, 0);
                planet = initCheckpoint(xrand5, yrand5, 60, 2);
            }
            TIMER++;
            
            
        }
        

        /* Echange du front et du back buffer : mise à jour de la fenêtre */
        SDL_GL_SwapBuffers();
        
        /* Boucle traitant les evenements */
        SDL_Event e;
        while(SDL_PollEvent(&e)) {
            /* L'utilisateur ferme la fenêtre : */
            if(e.type == SDL_QUIT) {
                loop = 0;
                break;
            }
            
            /* EVENTS */
            switch(e.type) {
                    
                case SDL_KEYUP:
                    if(e.key.keysym.sym == SDLK_LEFT ){
                        triggerD = 0;
                    }
                    if(e.key.keysym.sym == SDLK_RIGHT){
                        triggerD = 0;
                    }
                    if(e.key.keysym.sym == SDLK_UP ){
                        trigger = 0;
                    }
                    if(e.key.keysym.sym == SDLK_DOWN){
                        trigger = 0;
                    }
                    
                    break;
                    
                case SDL_KEYDOWN:
                    
                    //moteur
                    if(e.key.keysym.sym == SDLK_UP){
                        trigger = 4;
                        
                    }
                    if(e.key.keysym.sym == SDLK_DOWN){
                        trigger = 3;
                    }
                    
                    //couple
                    if(e.key.keysym.sym == SDLK_LEFT){
                        triggerD = 2;
                        
                    }
                    if(e.key.keysym.sym == SDLK_RIGHT){
                        triggerD = 1;
                    }
                    
                    //zoom
                    if(e.key.keysym.sym == SDLK_y){
                        if(etat1 == 1 && camZoom > 2.1)
                            camZoom -= 1;
                    }
                    if(e.key.keysym.sym == SDLK_h){
                        if(etat1 == 1 && camZoom < 5.1)
                            camZoom += 1;

                    }
                    if(e.key.keysym.sym == SDLK_ESCAPE){
                        camZoom = 2.1;
                        xmous = 1235;
                        ymous = 33;
                        etat1 = 0;
                    }
                    break;
                    
                case SDL_MOUSEBUTTONDOWN:
                    
                    if( e.type == SDL_MOUSEBUTTONDOWN )
                    {
                        //If the left mouse button was pressed
                        if( e.button.button == SDL_BUTTON_LEFT )
                        {
                            //Get the mouse offsets
                            xmous = e.button.x;
                            ymous = e.button.y;
                            
                            printf("%d  %d \n",xmous,ymous);
                        }
                    }
                    break;
                    
                case SDL_MOUSEMOTION:
                    if( e.type == SDL_MOUSEMOTION )
                    {
                        //Get the mouse offsets
                        xmousCont = e.motion.x;
                        ymousCont = e.motion.y;
                    }
                    break;
                    
                case SDL_VIDEORESIZE:
                    windowWidth  = e.resize.w;
                    windowHeight = e.resize.h;
                    setVideoMode(windowWidth, windowHeight);
                    reshape(windowWidth, windowHeight);
                    break;
                    
                default:
                    break;
                    
            }
        }
        /* Calcul du temps écoulé */
        Uint32 elapsedTime = SDL_GetTicks() - startTime;
        /* Si trop peu de temps s'est écoulé, on met en pause le programme */
        if(elapsedTime < FRAMERATE_MILLISECONDS) {
            SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
        }
    }
    
    /* Liberation des ressources associées à la SDL */
    SDL_Quit();
    
    return EXIT_SUCCESS;
}
