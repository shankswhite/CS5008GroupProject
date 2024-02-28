#ifndef TILE_H
#define TILE_H

enum TileState { BLANK, OBSTACLE, AGENT };

typedef struct Tile {
    int state;
    int point;
    int x;
    int y;
} Tile;

#endif // TILE_H
