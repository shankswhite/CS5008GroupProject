#include "gameLoop.h"
#include "map.h"
#include "gameManager.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int Score = 0;
int Box = 10;


void restart(){
    // reset level
    // reset map
    freeMap(mainMap);
    mainMap = newMap(1);

    // reset score
    Score = 0;

    // reset box
    Box = 10;
}

void putBox(int x, int y){
    if(Box <= 0){
        return;
    }
    if(x < 0 || x >= MAP_SIZE || y < 0 || y >= MAP_SIZE){
        return;
    }
    // if(mainMap->tileArray[x][y])
    mainMap->tileArray[x][y] = 5;
    Box--;
    return;
}

void updateMatrix(){}

void updateScore(){}

void nextRound(){}

void gameOver(){}

