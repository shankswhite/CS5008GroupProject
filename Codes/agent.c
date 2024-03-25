#include "map.h"
#include "level.h"
#include "gameManager.h"
#include "drawGraph.h"
#include "gameLogic.h"
#include "agent.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <math.h>



int curVisited[MAP_SIZE][MAP_SIZE] = {0};
int globalVisited[MAP_SIZE][MAP_SIZE];
int failedPath[MAP_SIZE][MAP_SIZE];
int path[MAP_SIZE * MAP_SIZE][2];
int pathIndex = 0;
int pathLength = 0;
int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; // UP, DOWN, LEFT, RIGHT


int agentNextMove(PathFindingAlgorithmPointer pfaP, Map_t* map, int agentLoc_x, int agentLoc_y, int endPointLoc_x, int endPointLoc_y) {
    return pfaP(map, agentLoc_x, agentLoc_y, endPointLoc_x, endPointLoc_y);
}

int nextStep(int currentX, int currentY, int nextX, int nextY) {
    // helper function to translate direction
    if (nextX == currentX - 1) return UP;
    if (nextX == currentX + 1) return DOWN;
    if (nextY == currentY - 1) return LEFT;
    if (nextY == currentY + 1) return RIGHT;
    return NO_FOUND;
}

int calculateDistance(int x1, int y1, int x2, int y2) {
    // helper function to be heuristic
    // return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
    return abs(x1 - x2) + abs(y1 - y2);
}


int isValid(Map_t* map, int x, int y) {
    if (x >= 0 && x < MAP_SIZE && y >= 0 && y < MAP_SIZE && 
        map->tileArray[x][y] < STATUS_OBSTACLE_BY_USER && 
        curVisited[x][y] != 1) {

        return 1;
    }
    return 0;
}


int dfs(Map_t* map, int agentLoc_x, int agentLoc_y, int endPointLoc_x, int endPointLoc_y) {
    if (curVisited[agentLoc_x][agentLoc_y] == 1 || 
        map->tileArray[agentLoc_x][agentLoc_y] >= STATUS_OBSTACLE_BY_USER) {
        // curVisited or obstacle
        return NO_FOUND;
    }

    path[pathIndex][0] = agentLoc_x;
    path[pathIndex][1] = agentLoc_y;
    pathIndex++;
    pathLength++;
    // printf("%d", pathIndex);
    // for (int i = 0; i < pathLength; i++) {
    //     printf("(%d, %d) ", path[i][0], path[i][1]);
    // }
    curVisited[agentLoc_x][agentLoc_y] = 1;

    if (agentLoc_x == endPointLoc_x && 
        agentLoc_y == endPointLoc_y) {
        // printf("******");
        int direction = NO_FOUND;
        if (pathIndex > 1) {
            direction = nextStep(path[pathIndex - 2][0], path[pathIndex - 2][1], 
                                 path[pathIndex - 1][0], path[pathIndex - 1][1]);
        }
        pathIndex--;
        return direction;
    }

    int minDistance = 100000;
    int bestDirection = NO_FOUND;

    for (int i = 0; i < 4; i++) {
        int new_x = agentLoc_x + directions[i][0];
        int new_y = agentLoc_y + directions[i][1];
        // printf("%d %d", new_x, new_y);
        if (new_x >= 0 && new_x < MAP_SIZE && new_y >= 0 && new_y < MAP_SIZE &&
            curVisited[new_x][new_y] == 0 &&
            map->tileArray[new_x][new_y] < STATUS_OBSTACLE_BY_USER) {
            int distance = calculateDistance(new_x, new_y, endPointLoc_x, endPointLoc_y);
            if (distance < minDistance) {
                curVisited[new_x][new_y] = 1; // Mark as curVisited
                if (dfs(map, new_x, new_y, endPointLoc_x, endPointLoc_y) != NO_FOUND) {
                    // printf("****");
                    minDistance = distance;
                    bestDirection = nextStep(agentLoc_x, agentLoc_y, new_x, new_y);
                    curVisited[new_x][new_y] = 0;
                    break; // Finding only one path is enough
                }
                curVisited[new_x][new_y] = 0;
            }
        }
    }

return bestDirection; 
}


// int dfsTest(Map_t* map, int agentLoc_x, int agentLoc_y, int endPointLoc_x, int endPointLoc_y) {
//     if (agentLoc_x == endPointLoc_x && agentLoc_y == endPointLoc_y) {
//         // 找到终点
//         path[pathIndex][0] = agentLoc_x;
//         path[pathIndex][1] = agentLoc_y;
//         pathIndex++;
//         return 1; // 成功找到终点
//     }

//     curVisited[agentLoc_x][agentLoc_y] = 1;
//     path[pathIndex][0] = agentLoc_x;
//     path[pathIndex][1] = agentLoc_y;
//     pathIndex++;
//     for (int i = 0; i < MAP_SIZE; i++) {
//         printf("%2d ", i);
//         for (int j = 0; j < MAP_SIZE; j++) {
//             printf("%d", curVisited[i][j]);
//         }
//         printf("\n");
//     }
//     // 重新初始化closestDistance和chosenDirection
//     int closestDistance = INT32_MAX;
//     int bestX = -1, bestY = -1;

//     // 探索所有方向
//     for (int i = 0; i < 4; i++) {
//         int new_x = agentLoc_x + directions[i][0];
//         int new_y = agentLoc_y + directions[i][1];
//         if (isValid(map, new_x, new_y)) {
//             int distance = calculateDistance(new_x, new_y, endPointLoc_x, endPointLoc_y);
//             if (distance < closestDistance && !curVisited[new_x][new_y]) {
//                 closestDistance = distance;
//                 bestX = new_x;
//                 bestY = new_y;
//             }
//         }
//     }

//     // 如果找到了一个更好的方向
//     if (bestX != -1 && dfsTest(map, bestX, bestY, endPointLoc_x, endPointLoc_y)) {
//         return 1; // 成功找到路径
//     }

//     // 回溯
//     pathIndex--;
//     curVisited[agentLoc_x][agentLoc_y] = 0;
//     return 0; 

// // }
// int dfsTest(Map_t* map, int agentLoc_x, int agentLoc_y, int endPointLoc_x, int endPointLoc_y) {
//     if (agentLoc_x == endPointLoc_x && agentLoc_y == endPointLoc_y) {
//         path[pathIndex][0] = agentLoc_x;
//         path[pathIndex][1] = agentLoc_y;
//         pathIndex++;
//         return 1;
//     }

//     curVisited[agentLoc_x][agentLoc_y] = 1;
//     path[pathIndex][0] = agentLoc_x;
//     path[pathIndex][1] = agentLoc_y;
//     pathIndex++;
//     for (int i = 0; i < MAP_SIZE; i++) {
//         printf("%2d ", i);
//         for (int j = 0; j < MAP_SIZE; j++) {
//             printf("%d", curVisited[i][j]);
//         }
//         printf("\n");
//     }
//     int closestDistance = INT32_MAX;
//     int chosenDirection = 0;

//     for (int i = 0; i < 4; i++) {
//         int new_x = agentLoc_x + directions[i][0];
//         int new_y = agentLoc_y + directions[i][1];
//         if (isValid(map, new_x, new_y) == 1) {
//             int distance = calculateDistance(new_x, new_y, endPointLoc_x, endPointLoc_y);
//             if (distance < closestDistance) {
//                 closestDistance = distance;
//                 chosenDirection = i;
//             }
//         }
//     }

//     if (chosenDirection != 0) {
//         int new_x = agentLoc_x + directions[chosenDirection][0];
//         int new_y = agentLoc_y + directions[chosenDirection][1];
//         if (dfsTest(map, new_x, new_y, endPointLoc_x, endPointLoc_y)) {
//             return 1;
//         }
//     }

//     pathIndex--;
//     curVisited[agentLoc_x][agentLoc_y] = 0;
//     return 0;
// }


// 当前最靠谱版本
int dfsTest(Map_t* map, int agentLoc_x, int agentLoc_y, int endPointLoc_x, int endPointLoc_y) {
    if (agentLoc_x == endPointLoc_x && agentLoc_y == endPointLoc_y) {
        // 找到终点
        path[pathIndex][0] = agentLoc_x;
        path[pathIndex][1] = agentLoc_y;
        pathIndex++;
        return 1;
    }

    curVisited[agentLoc_x][agentLoc_y] = 1;

    // for (int i = 0; i < MAP_SIZE; i++) {
    //     printf("%2d ", i);
    //     for (int j = 0; j < MAP_SIZE; j++) {
    //         printf("%d", curVisited[i][j]);
    //     }
    //     printf("\n");
    // }
    path[pathIndex][0] = agentLoc_x;
    path[pathIndex][1] = agentLoc_y;

    // printf("%d", pathIndex);
    // for (int i = 0; i < MAP_SIZE; i++) {
    //     printf("%2d ", i);
    //     for (int j = 0; j < MAP_SIZE; j++) {
    //         printf("%d", path[i][j]);
    //     }
    //     printf("\n");
    // }
    pathIndex++;

    int closestDistance = INT32_MAX;
    int nextStepIndex = -1; // 用于记录下一步的方向

    // 尝试所有方向
    for (int i = 0; i < 4; i++) {
        int new_x = agentLoc_x + directions[i][0];
        int new_y = agentLoc_y + directions[i][1];
        if (isValid(map, new_x, new_y) && !curVisited[new_x][new_y]) {
            int distance = calculateDistance(new_x, new_y, endPointLoc_x, endPointLoc_y);
            if (distance < closestDistance) {
                closestDistance = distance;
                nextStepIndex = i;
            }
        }
    }

    // 如果找到了一个方向
    if (nextStepIndex != -1) {
        int new_x = agentLoc_x + directions[nextStepIndex][0];
        int new_y = agentLoc_y + directions[nextStepIndex][1];
        if (dfsTest(map, new_x, new_y, endPointLoc_x, endPointLoc_y)) {
            return 1; // 成功找到路径
        }
    }

    // 回溯
    pathIndex--;
    curVisited[agentLoc_x][agentLoc_y] = 0;
    return 0;
}


int floodFillHelper(int x, int y, int endX, int endY, Map_t* map, int visited[MAP_SIZE][MAP_SIZE]) {
    if (x < 0 || x >= MAP_SIZE || y < 0 || y >= MAP_SIZE) return 0;
    if (visited[x][y] || map->tileArray[x][y] >= STATUS_OBSTACLE_BY_USER) return 0;

    if (x == endX && y == endY) { // Reached the destination
        path[pathIndex][0] = x;
        path[pathIndex][1] = y;
        pathIndex++;
        return 1;
    }

    curVisited[x][y] = 1; // Mark as visited
    path[pathIndex][0] = x; // 记录路径
    path[pathIndex][1] = y;
    pathIndex++;
    // for (int i = 0; i < MAP_SIZE; i++) {
    //     printf("%2d ", i);
    //     for (int j = 0; j < MAP_SIZE; j++) {
    //         printf("%d", curVisited[i][j]);
    //     }
    //     printf("\n");
    // }

    for (int j = 0; j < pathIndex; j++) {
        printf("(%d, %d)", path[j][0], path[j][1]);
    }


    for (int i = 0; i < 4; i++) {
        int newX = x + directions[i][0], newY = y + directions[i][1];

        if (floodFillHelper(newX, newY, endX, endY, map, visited)) return 1; // Found path
    }

    pathIndex--;
    return 0; // No path found
}





int findPath(int x, int y, int endX, int endY, Map_t* map) {
    memset(curVisited, 0, sizeof(curVisited)); // Ensure the visited array is cleared
    pathIndex = 0; // Reset path index for a new search

    if (floodFillHelper(x, y, endX, endY, map, curVisited)) {
        // Path found, can print or process path here if needed
        printf("Path found.\n");
        return 1;
    } else {
        printf("No path found.\n");
        return 0;
    }
}