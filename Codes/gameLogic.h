#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include "map.h"
#include <stdlib.h>
#include <string.h>

#define INITIAL_ROUND 0
#define INITIAL_SCORE 0
#define INITIAL_RSS 20

extern int g_round;
extern int g_score;
extern int g_rss;
extern int g_isGameEnd;
extern int g_isStuck;
extern int g_maxScore;

void checkGameOver();
int checkStuck(int startX, int startY, int endPointLoc_x, int endPointLoc_y, Map_t* map);
void updateScore();
void updateMapPastPath(Map_t* map, int loc_x, int loc_y);
void initGame();
void updateMapAgent(Map_t* map, int loc_x, int loc_y);
void restartGame();
void runDfs();
#endif
