#include "gameLoop.h"
#include "map.h"
#include "gameManager.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int Score = 0;
int Obstacle = 10;


void restart(){
    // reset level
    // reset map
    freeMap(mainMap);
    mainMap = newMap(1);

    // reset score
    Score = 0;

    // reset Obstacle
    Obstacle = 10;
}

void updateMatrix(int x, int y, int status){
    if(x < 0 || x >= MAP_SIZE || y < 0 || y >= MAP_SIZE){
        printf("Update failure");
        exit(1);
    }
    mainMap->tileArray[x][y] = status;
    return;
}

void updateScore(int change){
    Score += change;
    return;
}

void putObstacle(int x, int y){
    if(Obstacle <= 0){
        printf("no more obstacles");
        return;
    }
    //while(x < 0 || x >= MAP_SIZE || y < 0 || y >= MAP_SIZE){}
    if(x < 0 || x >= MAP_SIZE || y < 0 || y >= MAP_SIZE){
        printf("out of bound");
        return;
    }
    if(mainMap->tileArray[x][y] != STATUS_NULL){
        printf("invalid position");
        return;
    }
    updateMatrix(x, y, STATUS_OBSTACLE_BY_USER);
    Obstacle--;
    return;
}

void agentMove(int start_x, int start_y, int end_x, int end_y){
    if(end_x < 0 || end_x >= MAP_SIZE || end_y < 0 || end_y >= MAP_SIZE){
        printf("out of bound");
        return;
    }
    if(mainMap->tileArray[end_x][end_y] != STATUS_NULL){
        printf("invalid position");
        return;
    }
    updateMatrix(start_x, start_y, STATUS_AGENT_PAST);
    updateMatrix(end_x, end_y, STATUS_AGENT_CURR);
    updateScore(1);
    return;
}

void nextRound(){}

void gameOver(){}

