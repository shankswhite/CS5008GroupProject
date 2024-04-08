#include "map.h"
#include "level.h"

int g_agent_locx = START_X;
int g_agent_locy = START_Y;
int g_agent_prev_locx;
int g_agent_prev_locy;
int g_endPoint_locx = END_X;
int g_endPoint_locy = END_Y;
Coordinates START_COORDINATE = {START_X, START_Y};

Map_t createLevel1() {
    Map_t level1;

    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {
            level1.tileArray[i][j] = 0;
        }
    }

    level1.tileArray[0][0] = 1;
    level1.tileArray[19][19] = 2;

    return level1;
}

Map_t createLevel2() {
    Map_t level2;

    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {
            level2.tileArray[i][j] = 0;
        }
    }

    level2.tileArray[0][0] = 1;
    level2.tileArray[g_endPoint_locx][g_endPoint_locy] = 2;
    level2.tileArray[g_agent_locx][g_agent_locy] = 3;
    level2.tileArray[5][5] = 4;
    level2.tileArray[11][11] = 5;
    level2.tileArray[12][12] = 6;

    return level2;
}


Map_t createLevel3() {
    Map_t level3;

    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {
            level3.tileArray[i][j] = 0;
        }
    }

    level3.tileArray[19][19] = STATUS_END;
    for (int i = 0; i < MAP_SIZE - 1; i ++) {
        level3.tileArray[15][i] = STATUS_OBSTACLE_BY_USER;
    }

    for (int i = 1; i < MAP_SIZE; i ++) {
        level3.tileArray[10][i] = STATUS_OBSTACLE_BY_USER;
    }

    for (int i = 0; i < MAP_SIZE - 1; i ++) {
        level3.tileArray[5][i] = STATUS_OBSTACLE_BY_USER;
    }

    for (int i = 1; i < 5; i ++) {
        level3.tileArray[i][i] = STATUS_OBSTACLE_BY_USER;
    }

    for (int i = 11; i < 13; i ++) {
        level3.tileArray[i][10] = STATUS_OBSTACLE_BY_USER;
    }
    level3.tileArray[14][10] = STATUS_OBSTACLE_BY_USER;
    level3.tileArray[0][1] = STATUS_AGENT_CURR;
    level3.tileArray[19][19] = STATUS_END;

    return level3;
}


Map_t createLevel4() {
    Map_t level4;

    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {
            level4.tileArray[i][j] = 0;
        }
    }

    level4.tileArray[19][19] = STATUS_END;


    for (int i = 1; i < MAP_SIZE; i ++) {
        level4.tileArray[10][i] = STATUS_OBSTACLE_BY_USER;
    }


    return level4;
}


Map_t createLevel5() {
    Map_t level5;

    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {
            level5.tileArray[i][j] = 0;
        }
    }

    level5.tileArray[19][19] = STATUS_END;

    level5.tileArray[1][1] = STATUS_START;

    level5.tileArray[6][1] = STATUS_OBSTACLE_BY_USER;
    level5.tileArray[6][2] = STATUS_OBSTACLE_BY_USER;
    level5.tileArray[5][2] = STATUS_OBSTACLE_BY_USER;
    level5.tileArray[4][2] = STATUS_OBSTACLE_BY_USER;
    level5.tileArray[5][0] = STATUS_OBSTACLE_BY_USER;
    level5.tileArray[3][0] = STATUS_OBSTACLE_BY_USER;

    return level5;
}
