#ifndef MAP_H
#define MAP_H

#include "tile.h"

#define MAP_SIZE 20

typedef struct Map {
    Tile tiles[MAP_SIZE][MAP_SIZE];
    int length;
    int width;
} Map;

void updateMap(Map*);

#endif // MAP_H
