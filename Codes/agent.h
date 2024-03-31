#ifndef AGENT_H
#define AGENT_H

#include "map.h"

#define NO_FOUND 0
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4


typedef struct {
    int x, y;
} Point;

typedef struct {
    int x;
    int y;
} Coordinates;

typedef struct {
    Coordinates data[MAP_SIZE * MAP_SIZE]; // Maximum possible size
    int top;
} Stack;

extern int path[MAP_SIZE * MAP_SIZE][2];
extern int pathIndex;
extern int pathLength;
extern int visitCounts[20][20];

extern int curVisited[MAP_SIZE][MAP_SIZE];
int globalVisited[MAP_SIZE][MAP_SIZE];
extern Coordinates pathSteps[MAP_SIZE * MAP_SIZE];
extern Stack *s;

typedef int (*PathFindingAlgorithmPointer)(Map_t* map, int agentLoc_x, int agentLoc_y, int endPointLoc_x, int endPointLoc_y);


int agentNextMove(PathFindingAlgorithmPointer pfaP, Map_t* map, int agentLoc_x, int agentLoc_y, int endPointLoc_x, int endPointLoc_y);
// int dfs(Map_t* map, int agentLoc_x, int agentLoc_y, int endPointLoc_x, int endPointLoc_y);
// int dfsTest(Map_t* map, int agentLoc_x, int agentLoc_y, int endPointLoc_x, int endPointLoc_y);
int findPath(int x, int y, int endX, int endY, Map_t* map);
// Coordinates DFS(Map_t* map, Stack *stack, int dest_x, int dest_y);
void push(Stack *stack, Coordinates item);
// void dfsTest2(Map_t* map, Point start, Point end);
Coordinates dfsTest3(Map_t* map, Stack *stack, int dest_x, int dest_y);
void initialize(Stack *stack);
Coordinates getNextStep(Coordinates current);

// void updateMapAgent(Map_t* map, int agentLoc_x, int agentLoc_y);

#endif