#include "map.h"
#include "level.h"
#include "gameManager.h"
#include "drawGraph.h"
#include "gameLogic.h"
#include "agent.h"
// #include "main.c"

#include <stdio.h>
#include <GLUT/glut.h>
#include <OpenGL/gl.h>


int isNotEnoughError = 0;
int isStuckError = 0;
int isPastPathError = 0;
Map_t* mainMap = NULL;
Map_t* dfsMap = NULL;
Map_t* stuckMap = NULL;


void initWindow() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, WINDOW_WIDTH, WINDOW_HEIGHT, 0.0);
    glMatrixMode(GL_MODELVIEW);
}


Map_t* getMap() {
    Map_t mainLevel = createLevel5();
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
        if (g_score > g_maxScore) {
            g_maxScore = g_score;
        }
        drawWinMsg();
    }

    if (isStuckError == 1) {
        if (g_rss > 0) {
            drawStuckError();
        }
    }

    if (isPastPathError == 1) {
        drawPastPathError();
    }

    drawMaxScore();

    glutSwapBuffers();
}


void mouse(int button, int state, int x, int y) {

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {

        if (x >= BUTTON_NEXT_ROUND_X && x <= (BUTTON_NEXT_ROUND_X + BUTTON_WIDTH) && 
            y >= BUTTON_NEXT_ROUND_Y && y <= (BUTTON_NEXT_ROUND_Y + BUTTON_HEIGHT) && 
            g_isGameEnd == 0) {
            // TODO: Next round logic
            g_round++;
            updateMapPastPath(mainMap, g_agent_locx, g_agent_locy);
            
            runDfs();

            pathSteps[pathIndex] = (Coordinates){g_endPoint_locx, g_endPoint_locy};
            pathIndex++;

            for (int i = 0; i < pathIndex; i++) {
                printf("(%d, %d) \n", pathSteps[i].x, pathSteps[i].y);
            }

            printf("Next: (%d, %d)\n", pathSteps[g_round].x, pathSteps[g_round].y);
            g_agent_locx = pathSteps[g_round].x;
            g_agent_locy = pathSteps[g_round].y;
            
            updateMapAgent(mainMap, g_agent_locx, g_agent_locy);
            
            updateScore();            
        }

        int mapX = x / tileSize;
        int mapY = y / tileSize;

        if (isNotEnoughError == 1) {
            isNotEnoughError = 0;
        }

        if (isStuckError == 1) {
            isStuckError = 0;
        }

        if (isPastPathError == 1) {
            isPastPathError = 0;
        }

        if (mapX >= 0 && mapX < MAP_SIZE && mapY >= 0 && mapY < MAP_SIZE &&
            mainMap->tileArray[mapX][mapY] < STATUS_OBSTACLE_BY_USER &&
            mainMap->tileArray[mapX][mapY] != STATUS_AGENT_CURR) {
            // Update Map when the player put obstacles
            if (g_rss > 0) {
                int tempStatus = stuckMap->tileArray[mapX][mapY];
                updateMap(stuckMap, mapX, mapY, STATUS_OBSTACLE_BY_USER);
                // printf("%d \n", checkPastPath(mapX, mapY, g_endPoint_locx, g_endPoint_locy, mainMap));
                if (checkPastPath(mapX, mapY, g_endPoint_locx, g_endPoint_locy, mainMap) == 1) {
                    isPastPathError = 1;
                    // printf("Error: Past Path\n");
                    stuckMap->tileArray[mapX][mapY] = tempStatus;
                } else if (checkStuck(g_agent_locx, g_agent_locy, g_endPoint_locx, g_endPoint_locy, stuckMap) != 1) {
                    updateMap(mainMap, mapX, mapY, STATUS_OBSTACLE_BY_USER);
                    updateMap(dfsMap, mapX, mapY, STATUS_OBSTACLE_BY_USER);
                    g_rss--;
                } else {
                    isStuckError = 1;
                    stuckMap->tileArray[mapX][mapY] = tempStatus;
                }
            } else {
                isNotEnoughError = 1;
            }
        }

        if (x >= BUTTON_RESTART_X && x <= (BUTTON_RESTART_X + BUTTON_WIDTH) && 
            y >= BUTTON_RESTART_Y && y <= (BUTTON_RESTART_Y + BUTTON_HEIGHT)) {
            // TODO: Next round logic
            restartGame();
        }

        checkGameOver();
        glutPostRedisplay();
    }
}
