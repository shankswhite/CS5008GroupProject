#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H


#include "map.h"
#include "level.h"


#include <GLUT/glut.h>
#include <OpenGL/gl.h>


#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 800
#define MAP_WIDTH 800
#define MAP_HEIGHT 800

extern Map_t* mainMap;



void displayMap();
Map_t* getMap();
void display();
void initWindow();


#endif