#include "map.h"
#include "level.h"
#include "gameManager.h"
#include "drawGraph.h"

#include <stdio.h>
#include <GLUT/glut.h>
#include <OpenGL/gl.h>


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

Map_t* mainMap = NULL;

// 绘制函数
void display() {

    glClear(GL_COLOR_BUFFER_BIT); // 清除颜色缓冲区
    glLoadIdentity(); // 重置当前指定的矩阵为单位矩阵

    drawMap();

    drawGrid();

    drawDescription();

    drawScore();

    drawButton();


    glutSwapBuffers(); // 确保之前的所有OpenGL命令已经执行完毕
}



