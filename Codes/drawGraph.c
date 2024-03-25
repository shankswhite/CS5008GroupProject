#include "drawGraph.h"
#include "gameManager.h"

#include <stdio.h>
#include <GLUT/glut.h>
#include <OpenGL/gl.h>

float tileSize = MAP_WIDTH / MAP_SIZE;


void setColorByStatus(int status) {
    switch (status) {
        case STATUS_NULL:
            glColor3f(1.0, 1.0, 1.0); // White
            break;
        case STATUS_END:
            glColor3f(0.0, 2.0, 0.0); // Bright Green (assuming it's yellowish)
            break;
        case STATUS_AGENT_CURR:
            glColor3f(1.0, 0.0, 0.0); // Red
            break;
        case STATUS_AGENT_PAST:
            glColor3f(1, 0.8, 0.8); // Light Red
            break;
        case STATUS_OBSTACLE_BY_USER:
        case STATUS_OBSTACLE_BY_DEFAULT:
            glColor3f(0.0, 0.0, 0.0); // Black
            break;
            
        default:
            glColor3f(1.0, 1.0, 1.0); // Default Color: white
            break;
    }
}

void drawGrid() {
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(2.0);
    
    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {
            glBegin(GL_LINE_LOOP);

            glVertex2f(i * tileSize, j * tileSize);
            glVertex2f((i + 1) * tileSize, j * tileSize);
            glVertex2f((i + 1) * tileSize, (j + 1) * tileSize);
            glVertex2f(i * tileSize, (j + 1) * tileSize);

            glEnd();
        }
    }
}


void drawMap() {
    // Draw the matrix map into the window.

    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {
            setColorByStatus(mainMap->tileArray[i][j]);
            glBegin(GL_QUADS);
                glVertex2f(i * tileSize, j * tileSize);
                glVertex2f((i + 1) * tileSize, j * tileSize);
                glVertex2f((i + 1) * tileSize, (j + 1) * tileSize);
                glVertex2f(i * tileSize, (j + 1) * tileSize);
            glEnd();
        }
    }
}

void renderString(float x, float y, const char *string) {
    const char *c;
    glRasterPos2f(x, y);
    for (c = string; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }
}


void renderStringSmall(float x, float y, const char *string) {
    const char *c;
    glRasterPos2f(x, y);
    for (c = string; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *c);
    }
}


void renderBox(float x, float y, int status) {
    glBegin(GL_QUADS);
                glVertex2f(x, y);
                glVertex2f(x + tileSize, y);
                glVertex2f(x + tileSize, y + tileSize);
                glVertex2f(x, y + tileSize);
    glEnd();
}

void renderWidget(float x, float y, int status, const char* string) {
    setColorByStatus(status);

    renderBox(x, y - 25, status);
    renderString(x + 50, y, string);
}


void drawDescription() {
    renderWidget(MAP_WIDTH+10, 40, STATUS_END, "End Point");
    renderWidget(MAP_WIDTH+10, 80, STATUS_AGENT_CURR, "Agent");
    renderWidget(MAP_WIDTH+10, 120, STATUS_AGENT_PAST, "Past Path");
    renderWidget(MAP_WIDTH+10, 160, STATUS_OBSTACLE_BY_USER, "Obstacles");

    renderStringSmall(810, 220, "Your Goal: ");
    renderStringSmall(810, 240, "1. Click Tiles to ");
    renderStringSmall(810, 260, "place Obstacles,");
    renderStringSmall(810, 280, "2. Prevent Agent from");
    renderStringSmall(810, 300, "Reaching End Point.");
    renderStringSmall(810, 320, "3. The more Tiles");
    renderStringSmall(810, 340, "Agent travels, ");
    renderStringSmall(810, 360, "The more Scores.");

}


void drawScore() {
    renderString(810, 400, "Score: ");
    //TODO: Modify score
    renderString(900, 400, "0");

    renderString(810, 430, "RSS: ");
    //TODO: Modify box number
    renderString(870, 430, "0");
}


void renderButton(float x, float y, const char* string) {
    glColor3f(0.5, 0.8, 0.5);
    glBegin(GL_QUADS);
        glVertex2f(x, y);
        glVertex2f(x+BUTTON_WIDTH, y);
        glVertex2f(x+BUTTON_WIDTH, y+BUTTON_HEIGHT);
        glVertex2f(x, y+BUTTON_HEIGHT);
    glEnd();

    glColor3f(0, 0, 0);
    renderString(x+20, y + 25, string);
}


void drawButton() {
    renderButton(BUTTON_NEXT_ROUND_X, BUTTON_NEXT_ROUND_Y, "Next Round");
    renderButton(BUTTON_RESTART_X, BUTTON_RESTART_Y, "Restart");
    renderButton(BUTTON_AGENT_X, BUTTON_AGENT_Y, "Agent: DFS");
}


void drawMask() {
    glColor3f(0.5, 0.8, 0.5);
    glBegin(GL_QUADS);
        glVertex2f(MAP_WIDTH+1, 651);
        glVertex2f(WINDOW_WIDTH, 651);
        glVertex2f(WINDOW_WIDTH, 800);
        glVertex2f(MAP_WIDTH+1, 800);
    glEnd();
}


void drawNotEnoughError() {
    glColor3f(1, 0, 0);
    glBegin(GL_QUADS);
        glVertex2f(MAP_WIDTH+1, 651);
        glVertex2f(WINDOW_WIDTH, 651);
        glVertex2f(WINDOW_WIDTH, 700);
        glVertex2f(MAP_WIDTH+1, 700);
    glEnd();

    glColor3f(1, 1, 1);
    renderString(MAP_WIDTH+10, 675, "Not Enough Box!");
}


void drawWinMsg() {
    glColor3f(0, 0.5, 0.5);
    glBegin(GL_QUADS);
        glVertex2f(MAP_WIDTH+1, 710);
        glVertex2f(WINDOW_WIDTH, 710);
        glVertex2f(WINDOW_WIDTH, 800);
        glVertex2f(MAP_WIDTH+1, 800);
    glEnd();

    glColor3f(1, 0, 0);
    renderString(MAP_WIDTH+10, 735, "Game Over");
    renderString(MAP_WIDTH+10, 750, "Final Score:");
    renderString(MAP_WIDTH+80, 765, "0");
}