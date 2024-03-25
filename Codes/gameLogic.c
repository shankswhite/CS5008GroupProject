#include "gameLogic.h"
#include "gameManager.h"

int g_round = INITIAL_ROUND;
int g_score = INITIAL_SCORE;
int g_rss = INITIAL_RSS;
int g_isGameEnd = 0;
int g_isStuck = 0;



void checkGameOver() {
    if (g_agent_locx == g_endPoint_locx &&
        g_agent_locy == g_endPoint_locy) {
            g_isGameEnd = 1;
        }
}


int floodFill(int x, int y, int endPointLoc_x, int endPointLoc_y, Map_t* map, int visited[MAP_SIZE][MAP_SIZE]) {
    if (x < 0 || x >= MAP_SIZE || y < 0 || y >= MAP_SIZE) {
        return 0;
    }

    if (visited[x][y] || map->tileArray[x][y] >= STATUS_OBSTACLE_BY_USER) {
        return 0;
    }

    visited[x][y] = 1;

    if (x == endPointLoc_x && y == endPointLoc_y) {
        return 1;
    }

    if (floodFill(x + 1, y, endPointLoc_x, endPointLoc_y, map, visited)) return 1;
    if (floodFill(x - 1, y, endPointLoc_x, endPointLoc_y, map, visited)) return 1;
    if (floodFill(x, y + 1, endPointLoc_x, endPointLoc_y, map, visited)) return 1;
    if (floodFill(x, y - 1, endPointLoc_x, endPointLoc_y, map, visited)) return 1;

    return 0;
}


int checkStuck(int startX, int startY, int endPointLoc_x, int endPointLoc_y, Map_t* map) {
    int visited[MAP_SIZE][MAP_SIZE] = {0};
    return !floodFill(startX, startY, endPointLoc_x, endPointLoc_y, map, visited);
}


void updateScore() {
    g_score++;
}

void updateMapPastPath() {

}

