#include "map.h"
#include "level.h"
#include "gameManager.h"
#include "drawGraph.h"
#include "gameLogic.h"
#include "agent.h"

#include <stdio.h>
#include <GLUT/glut.h>
#include <OpenGL/gl.h>


int isNotEnoughError = 0;
int isStuckError = 0;
Map_t* mainMap = NULL;


void initWindow() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, WINDOW_WIDTH, WINDOW_HEIGHT, 0.0);
    glMatrixMode(GL_MODELVIEW);
}


Map_t* getMap() {
    Map_t mainLevel = createLevel2();
    Map_t* mainMap = newMap(mainLevel);
    return mainMap;
}


void display() {

    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    drawMap();

    drawGrid();

    drawDescription();

    drawScore();

    drawButton();

    if (isNotEnoughError == 1) {
        drawNotEnoughError();
    }

    if (g_isGameEnd == 1) {
        drawWinMsg();
    }

    glutSwapBuffers();
}


void mouse(int button, int state, int x, int y) {

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        checkGameOver();

        if (x >= BUTTON_NEXT_ROUND_X && x <= (BUTTON_NEXT_ROUND_X + BUTTON_WIDTH) && 
            y >= BUTTON_NEXT_ROUND_Y && y <= (BUTTON_NEXT_ROUND_Y + BUTTON_HEIGHT)) {
            // TODO: Next round logic
            // updateMapAgent(mainMap, g_agent_locx, g_agent_locy);
            // updateMapPastPath();
            // updateScore();
            // reset visited

        }

        int mapX = x / tileSize;
        int mapY = y / tileSize;

        if (isNotEnoughError == 1) {
            isNotEnoughError = 0;
        }

        if (isStuckError == 1) {
            isStuckError = 0;
        }

        if (mapX >= 0 && mapX < MAP_SIZE && mapY >= 0 && mapY < MAP_SIZE &&
            mainMap->tileArray[mapX][mapY] == STATUS_NULL) {
            // Update Map when the player put obstacles
            if (g_rss > 0) {
                // TODO checkStuck call
                // if (checkStuck() != 1) {
                //     updateMap(mainMap, mapX, mapY, STATUS_OBSTACLE_BY_USER);
                //     g_rss--;
                // } else {
                //     isStuckError = 1;
                //     mainMap->tileArray[mapX][mapY] = STATUS_NULL;
                // }
                
            } else {
                isNotEnoughError = 1;
            }
        }

        glutPostRedisplay();
    }
}
