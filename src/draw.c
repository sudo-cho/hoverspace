#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "draw.h"

void dessincarre(){
    glBegin(GL_POLYGON);
    glVertex2f(-0.5,-0.5);
    glVertex2f(-0.5,1.5);
    glVertex2f(1.5,1.5);
    glVertex2f(0.5,-0.5);
    glEnd();
}

void dessincercle(int a){
    if (a==0)
        glBegin(GL_LINE_LOOP);
    else
        glBegin(GL_POLYGON);
    float i;
    for(i=0; i<100; i+=0.1){
        glVertex2f(0.5*cos(i),0.5*sin(i));
    }
    glEnd();
}

void dessinCarreRond(){
    glPushMatrix();
    glTranslatef(-2.5,5,0.0);
    glScalef(5.0,5.0,0.0);
    dessincercle(1);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-2.5,-5,0.0);
    glScalef(5.0,5.0,0.0);
    dessincercle(1);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(2.5,-5,0.0);
    glScalef(5.0,5.0,0.0);
    dessincercle(1);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(2.5,5,0.0);
    glScalef(5.0,5.0,0.0);
    dessincercle(1);
    glPopMatrix();
    
    glPushMatrix();
    glScalef(5.0,15.0,0.0);
    dessincarre();
    glPopMatrix();
    
    glPushMatrix();
    glScalef(10.0,10.0,0.0);
    dessincarre();
    glPopMatrix();
}
