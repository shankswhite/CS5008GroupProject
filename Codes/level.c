#include "map.h"
#include "level.h"

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