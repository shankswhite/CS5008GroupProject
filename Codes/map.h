#ifndef MAP_H
#define MAP_H


#define MAP_SIZE 20
#define STATUS_NULL 0
#define STATUS_START 1
#define STATUS_END 2
#define STATUS_AGENT_CURR 3
#define STATUS_AGENT_PAST 4
#define STATUS_OBSTACLE_BY_USER 5
#define STATUS_OBSTACLE_BY_DEFAULT 6


typedef struct Map {
    int tileArray[MAP_SIZE][MAP_SIZE];
} Map_t;
// 0 Space/NULL
// 1 Start Point
// 2 Win Point
// 3 Agent Current Location
// 4 Agent Past Location
// 5 Obstacles Put by User
// 6 Obstacles Put by Default


void updateMap(Map_t* map, int loc_x, int loc_y, int newState);
int tileStatus(Map_t* map, int loc_x, int loc_y); // Check the sepcific tile's status/number to judge if it could be put obstacle or else
Map_t* newMap(Map_t);
void printMap(Map_t* map);
void freeMap(Map_t* map);

#endif
