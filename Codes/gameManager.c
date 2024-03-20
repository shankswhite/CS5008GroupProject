#include "map.h"
#include "level.h"
#include "gameManager.h"
#include "drawGrid.h"

#include <stdio.h>
#include <GLUT/glut.h>
#include <OpenGL/gl.h>


void initOpenGL() {
    glClearColor(1.0, 0.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, WINDOW_WIDTH, WINDOW_HEIGHT, 0.0);
    glMatrixMode(GL_MODELVIEW);
}

Map_t* getMap() {
    Map_t mainLevel = createLevel1();
    Map_t* mainMap = newMap(mainLevel);
    return mainMap;
}

Map_t* mainMap = NULL;


// 绘制函数
void displayMap() {

    glClear(GL_COLOR_BUFFER_BIT); // 清除颜色缓冲区
    glLoadIdentity(); // 重置当前指定的矩阵为单位矩阵
    // drawGrid();

    // 假设每个tile的大小
    float tileSize = MAP_WIDTH / 20.0;

    // 遍历你的地图数据并绘制每个tile
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            if (mainMap->tileArray[i][j] == 0) {
                glColor3f(1.0, 1.0, 1.0); // 设置颜色为白色
            } else {
                
                glColor3f(0.0, 0.0, 0.0); // 设置颜色为黑色
            }
            // 绘制正方形tile
            glBegin(GL_QUADS);
                glVertex2f(i * tileSize, j * tileSize);
                glVertex2f((i + 1) * tileSize, j * tileSize);
                glVertex2f((i + 1) * tileSize, (j + 1) * tileSize);
                glVertex2f(i * tileSize, (j + 1) * tileSize);
            glEnd();
        }
    }

    glBegin(GL_QUADS);
        glVertex2f(800, 900);
        glVertex2f(900, 900);
        glVertex2f(900, 700);
        glVertex2f(800, 700);
    glEnd();


    glFlush(); // 确保之前的所有OpenGL命令已经执行完毕
}



int display(int argc, char** argv) {
    mainMap = getMap();
    

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Map");

    // 设置绘制回调函数
    glutDisplayFunc(displayMap);

    initOpenGL();

    // 进入GLUT事件处理循环
    glutMainLoop();
    if (mainMap) {
        freeMap(mainMap);
        mainMap = NULL;
    }

    return 0;
}



