#ifndef DRAWGRAPH_H
#define DRAWGRAPH_H

#include <GLUT/glut.h>
#include <OpenGL/gl.h>

#define BUTTON_NEXT_ROUND_X MAP_WIDTH+30
#define BUTTON_NEXT_ROUND_Y 550
#define BUTTON_RESTART_X MAP_WIDTH+30
#define BUTTON_RESTART_Y 600
#define BUTTON_AGENT_X MAP_WIDTH+30
#define BUTTON_AGENT_Y 650

#define BUTTON_WIDTH 140
#define BUTTON_HEIGHT 40

extern float tileSize;


void drawGrid();
void drawMap();
void drawButton();
void drawDescription();
void drawScore();
void drawMask();
void drawNotEnoughError();
void drawWinMsg();

#endif
