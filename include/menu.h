#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "hovercraft.h"

#ifndef MENU
#define MENU

int cas( int x, int y);
void boutonMenu( int x, int y, int xdec, int ydec);
void initTextureMenu(GLuint *textureIdMenu);
void afficherMenu(hovercraft *hover, GLuint *textureIdMenu);
void initTextureMenu2(GLuint *textureIdMenu2);
void afficherMenu2(hovercraft *hover, GLuint *textureIdMenu2);
void initTextureMenuWin(GLuint *textureIdMenuWin);
void afficherMenuWin(hovercraft *hover, GLuint *textureIdMenuWin);
void initTextureMenuLose(GLuint *textureIdMenuLose);
void afficherMenuLose(hovercraft *hover, GLuint *textureIdMenuLose);
void initTextureBackground(GLuint *textureIdBackground);
void background(int x1, int x2, int y1, int y2, GLuint *textureIdBackground);
  

#endif 
