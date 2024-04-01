// gcc -fdiagnostics-color=always -g map.c level.c drawGraph.c gameManager.c main.c -o mainProgram -framework OpenGL -framework GLUT -Wno-deprecated-declarations

#include "map.h"
#include "agent.h"
#include "user.h"
#include "map.h"
#include "level.h"
#include "gameManager.h"
#include "gameLogic.h"

#include <stdio.h>
#include <GLUT/glut.h>
#include <OpenGL/gl.h>


int main(int argc, char** argv) {
    // initialize the map
    mainMap = getMap();
    dfsMap = getMap();
    stuckMap = getMap();

    // initialize data for dfs and start point
    initGame();

    
    

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Tile Conqueror");

    glutDisplayFunc(display);
    glutMouseFunc(mouse);

    initWindow();

    glutMainLoop();
    if (mainMap) {
        freeMap(mainMap);
        mainMap = NULL;
    }

    if (dfsMap) {
        freeMap(dfsMap);
        dfsMap = NULL;
    }

    if (stuckMap) {
        freeMap(stuckMap);
        stuckMap = NULL;
    }

    

    return 0;
}
