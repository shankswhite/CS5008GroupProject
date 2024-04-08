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
extern Map_t* dfsMap;
extern Map_t* stuckMap;
extern int isNotEnoughError;
extern int isStuckError;


Map_t* getMap();
void display();
void initWindow();
void mouse(int button, int state, int x, int y);


#endif
