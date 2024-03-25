#include "map.h"

#define INITIAL_ROUND 0
#define INITIAL_SCORE 0
#define INITIAL_RSS 3

extern int g_round;
extern int g_score;
extern int g_rss;
extern int g_isGameEnd;
extern int g_isStuck;

void checkGameOver();
int checkStuck(int startX, int startY, int endPointLoc_x, int endPointLoc_y, Map_t* map);
void updateScore();
void updateMapPastPath();
