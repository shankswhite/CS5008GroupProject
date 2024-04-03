#include "gameLogic.h"
#include "agent.h"
#include "gameManager.h"

#include <stdio.h>

int g_round = INITIAL_ROUND;
int g_score = INITIAL_SCORE;
int g_rss = INITIAL_RSS;
int g_isGameEnd = 0;
int g_isStuck = 0;
int g_maxScore = 0;


void checkGameOver() {
    if (g_agent_locx == g_endPoint_locx &&
        g_agent_locy == g_endPoint_locy) {
            g_isGameEnd = 1;
            printf("Game Over\nGame Over\nGame Over\nGame Over\nGame Over\nGame Over");
        }
}


int floodFill(int x, int y, int endPointLoc_x, int endPointLoc_y, Map_t* map, int visited[MAP_SIZE][MAP_SIZE]) {
    if (x < 0 || x >= MAP_SIZE || y < 0 || y >= MAP_SIZE) {
        printf("Out of bounds\n");
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


int floodFillUtil(int x, int y, int endPointLoc_x, int endPointLoc_y, Map_t* map, int visited[MAP_SIZE][MAP_SIZE]) {
    if (x < 0 || x >= MAP_SIZE || y < 0 || y >= MAP_SIZE) return 0;
    if (visited[x][y] || map->tileArray[x][y] >= STATUS_OBSTACLE_BY_USER) return 0;

    visited[x][y] = 1;

    if (x == endPointLoc_x && y == endPointLoc_y) return 1;

    if (floodFillUtil(x + 1, y, endPointLoc_x, endPointLoc_y, map, visited)) return 1;
    if (floodFillUtil(x - 1, y, endPointLoc_x, endPointLoc_y, map, visited)) return 1;
    if (floodFillUtil(x, y + 1, endPointLoc_x, endPointLoc_y, map, visited)) return 1;
    if (floodFillUtil(x, y - 1, endPointLoc_x, endPointLoc_y, map, visited)) return 1;

    return 0;
}


int checkStuck(int startX, int startY, int endPointLoc_x, int endPointLoc_y, Map_t* map) {
    int visited[MAP_SIZE][MAP_SIZE] = {0};
    return !floodFillUtil(startX, startY, endPointLoc_x, endPointLoc_y, map, visited);
}


void updateScore() {
    if (g_isGameEnd == 0) {
        g_score++;
    }
}


void updateMapPastPath(Map_t* map, int loc_x, int loc_y) {
    map->tileArray[loc_x][loc_y] = STATUS_AGENT_PAST;
}


void updateMapAgent(Map_t* map, int loc_x, int loc_y) {
    map->tileArray[loc_x][loc_y] = STATUS_AGENT_CURR;

}


void initGame() {
    mainMap->tileArray[START_X][START_Y] = STATUS_AGENT_CURR;
    // Stack stack;
    // initialize(&stack);
    // push(&stack, (Coordinates){START_X, START_Y});

    // Coordinates nextStep = {-1, -1};
    // printf("Start: (%d, %d)\n", nextStep.x, nextStep.y);
    // printf("Start: (%d, %d)\n", start_x, start_y);
}


void runDfs() {
    Stack stack;
    initialize(&stack);
    push(&stack, (Coordinates){START_X, START_Y});
    pathIndex = 0;
    Coordinates nextStep = {START_X, START_Y};
    Map_t* tempMap = (Map_t*)malloc(sizeof(Map_t));
    if (tempMap == NULL) {
        exit(1);
    }

    memcpy(tempMap, dfsMap, sizeof(Map_t));

    while (!(nextStep.x == g_endPoint_locx && nextStep.y == g_endPoint_locy)) {
        nextStep = dfsTest3(tempMap, &stack, g_endPoint_locx, g_endPoint_locy);
        // printf("Next step: (%d, %d)\n", nextStep.x, nextStep.y);
    }

    printf("%d \n", pathIndex);
    free(tempMap);
}


void restartGame() {
    mainMap = getMap();
    dfsMap = getMap();
    g_round = INITIAL_ROUND;
    g_score = INITIAL_SCORE;
    g_rss = INITIAL_RSS;
    g_isGameEnd = 0;
    g_isStuck = 0;
    g_agent_locx = START_X;
    g_agent_locy = START_Y;
    g_endPoint_locx = END_X;
    g_endPoint_locy = END_Y;
    // mainMap->tileArray[START_X][START_Y] = STATUS_AGENT_CURR;
    initGame();
    display();
}
