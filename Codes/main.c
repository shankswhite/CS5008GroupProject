// gcc -fdiagnostics-color=always -g map.c level.c drawGraph.c gameManager.c main.c -o mainProgram -framework OpenGL -framework GLUT -Wno-deprecated-declarations

#include "map.h"
#include "agent.h"
#include "user.h"
#include "map.h"
#include "level.h"
#include "gameManager.h"

#include <stdio.h>
#include <GLUT/glut.h>
#include <OpenGL/gl.h>


int main(int argc, char** argv) {
    mainMap = getMap();
    

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

    return 0;
}
