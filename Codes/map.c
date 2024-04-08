#include "map.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void updateMap(Map_t* map, int loc_x, int loc_y, int newState) {
    map->tileArray[loc_x][loc_y] = newState;
}

int tileStatus(Map_t* map, int loc_x, int loc_y) {
    return map->tileArray[loc_x][loc_y];
}

Map_t* newMap(Map_t level) {
    Map_t* map = (Map_t*)calloc(1, sizeof(Map_t));
    if (map == NULL) {
        return NULL;
    }

    memcpy(map, &level, sizeof(Map_t));

    return map;    
}

void freeMap(Map_t* map) {
    if (map == NULL) {
        return;
    }

    free(map);
}

void printMap(Map_t* map) {
    for (int i = 0; i < MAP_SIZE; i++) {
        printf("%2d ", i);
        for (int j = 0; j < MAP_SIZE; j++) {
            printf("%d", map->tileArray[i][j]);
        }
        printf("\n");
    }
    return;
}