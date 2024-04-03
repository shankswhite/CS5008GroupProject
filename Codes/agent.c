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

#define INF 10000
int newPath[MAP_SIZE * MAP_SIZE][2];
int newPathIndex = 0;
Coordinates pathSteps[MAP_SIZE * MAP_SIZE];
int visitCounts[20][20] = {0};

int curVisited[MAP_SIZE][MAP_SIZE] = {0};
int globalVisited[MAP_SIZE][MAP_SIZE] = {0};
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
        map->tileArray[x][y] < STATUS_OBSTACLE_BY_USER) {

        return 1;
    }
    return 0;
}


int is_valid_step_by_step_path() {
    for (int i = 0; i < pathLength - 1; i++) {
        int dx = abs(path[i][0] - path[i + 1][0]);
        int dy = abs(path[i][1] - path[i + 1][1]);

        if (!((dx == 1 && dy == 0) || (dx == 0 && dy == 1))) {
            printf("Invalid move from (%d, %d) to (%d, %d) at step %d.\n", 
                   path[i][0], path[i][1], path[i + 1][0], path[i + 1][1], i + 1);
            return 0;
        }
    }
    return 1;
}

void optimizePath() {
    if (pathIndex == 0) return;

    newPath[newPathIndex][0] = path[0][0];
    newPath[newPathIndex][1] = path[0][1];
    newPathIndex++;

    for (int i = 1; i < pathIndex - 1; i++) {
        int dx1 = path[i][0] - path[i-1][0];
        int dy1 = path[i][1] - path[i-1][1];
        int dx2 = path[i+1][0] - path[i][0];
        int dy2 = path[i+1][1] - path[i][1];

        if (dx1 != dx2 || dy1 != dy2) {
            newPath[newPathIndex][0] = path[i][0];
            newPath[newPathIndex][1] = path[i][1];
            newPathIndex++;
        }
    }

    newPath[newPathIndex][0] = path[pathIndex - 1][0];
    newPath[newPathIndex][1] = path[pathIndex - 1][1];
    newPathIndex++;
}

void printNewPath() {
    for (int i = 0; i < newPathIndex; i++) {
        printf("(%d, %d) -> ", newPath[i][0], newPath[i][1]);
    }
    printf("End\n");
}

int floodFillHelper(int x, int y, int endX, int endY, Map_t* map, int visited[MAP_SIZE][MAP_SIZE]) {
    if (x < 0 || x >= MAP_SIZE || y < 0 || y >= MAP_SIZE) return 0;
    if (visited[x][y] || map->tileArray[x][y] >= STATUS_OBSTACLE_BY_USER) return 0;

    if (x == endX && y == endY) {

        return 1;
    }

    curVisited[x][y] = 1;

    // for (int i = 0; i < MAP_SIZE; i++) {
    //     printf("%2d ", i);
    //     for (int j = 0; j < MAP_SIZE; j++) {
    //         printf("%d", curVisited[i][j]);
    //     }
    //     printf("\n");
    // }

    // for (int j = 0; j < pathIndex; j++) {
    //     printf("(%d, %d)", path[j][0], path[j][1]);
    // }

    // printf("\n is valid? -> %d \n", is_valid_step_by_step_path());

    // optimizePath();
    // printNewPath();


    for (int i = 0; i < 4; i++) {
        int newX = x + directions[i][0], newY = y + directions[i][1];

        if (floodFillHelper(newX, newY, endX, endY, map, visited)) return 1;
    }


    return 0;
}

int findPath(int x, int y, int endX, int endY, Map_t* map) {
    memset(curVisited, 0, sizeof(curVisited));
    // TODO: free mem

    if (floodFillHelper(x, y, endX, endY, map, curVisited)) {
        printf("Path found.\n");
        return 1;
    } else {
        printf("No path found.\n");
        return 0;
    }
}

void shuffleDirections(int distances[], int indexes[], int size) {
    for (int i = 0; i < size; ++i) {
        int j = rand() % (i + 1);
        // 交换distances
        int temp = distances[i];
        distances[i] = distances[j];
        distances[j] = temp;
        // 交换indexes
        temp = indexes[i];
        indexes[i] = indexes[j];
        indexes[j] = temp;
    }
}



void initialize(Stack *stack) {
    stack->top = -1;
}

int isEmpty(Stack *stack) {
    return stack->top == -1;
}

void push(Stack *stack, Coordinates item) {
    if (stack->top == MAP_SIZE * MAP_SIZE - 1) {
        printf("Stack overflow\n");
        return;
    }
    stack->data[++stack->top] = item;
}

Coordinates pop(Stack *stack) {
    if (isEmpty(stack)) {
        printf("Stack underflow\n");
        exit(1);
    }
    return stack->data[stack->top--];
}

// DFS algorithm to find the shortest path
Coordinates dfsTest3(Map_t* map, Stack *stack, int dest_x, int dest_y) {
    Coordinates next_step;
    Coordinates current;
    current = pop(stack);
    pathSteps[pathIndex++] = current;
    globalVisited[current.x][current.y] = 1;
    // for (int i = 0; i < MAP_SIZE; i++) {
    //     printf("%2d ", i);
    //     for (int j = 0; j < MAP_SIZE; j++) {
    //         printf("%d", curVisited[i][j]);
    //     }
    //     printf("\n");
    // }
    int nx, ny;

    // Possible moves (right, down, left, up)
    int dx[] = {1, 0, -1, 0};
    int dy[] = {0, 1, 0, -1};

    for (int i = 0; i < 4; ++i) {
        nx = current.x + dx[i];
        ny = current.y + dy[i];

        // Check if the next move is within bounds and not an obstacle
        if (nx >= 0 && nx < MAP_SIZE && ny >= 0 && ny < MAP_SIZE &&
            tileStatus(map, nx, ny) != STATUS_OBSTACLE_BY_USER &&
            tileStatus(map, nx, ny) != STATUS_OBSTACLE_BY_DEFAULT &&
            tileStatus(map, nx, ny) != STATUS_AGENT_PAST) {

            // Move to the next location
            next_step.x = nx;
            next_step.y = ny;
            updateMap(map, nx, ny, STATUS_AGENT_PAST);
            push(stack, current);

            // Check if the destination is reached
            if (nx == dest_x && ny == dest_y) {
                return next_step;
            }
            // if (!(next_step.x == -1 && next_step.y == -1)) {
            //     pathSteps[pathIndex++] = next_step;
            // }

            // Push the next step to the stack for further exploration
            push(stack, next_step);
            return next_step; // Return the next step to continue traversal in main
        }
    }

    // If no valid move found, return current position
    return current;
}


Coordinates getNextStep(Coordinates current) {
    
    int currentVisitCount = visitCounts[current.x][current.y];
    printf("%d\n", currentVisitCount);
    int count = 0;

    for (int i = 0; i < pathIndex - 1; i++) { 
        if (pathSteps[i].x == current.x && pathSteps[i].y == current.y) {
            count++;
            if (count == currentVisitCount) {

                if (i + 1 < pathIndex) {
                    visitCounts[current.x][current.y]++;
                    return pathSteps[i + 1];
                } else {
                    visitCounts[current.x][current.y]++;
                    return (Coordinates){-1, -1};
                }
            }
        }
    }
    visitCounts[current.x][current.y]++;
    return (Coordinates){-1, -1};
}







// int main() {
//     // Initialize a map
//     Map_t testLevel = createLevel3();
//     Map_t* map = newMap(testLevel);


//     printf("Status of tile at position (4, 0): %d\n", tileStatus(map, 4, 0));

//     // Set start and end points
//     int start_x = 0;
//     int start_y = 1;
//     int dest_x = 19;
//     int dest_y = 19;

//     Stack stack;
//     initialize(&stack);
//     push(&stack, (Coordinates){start_x, start_y});

//     Coordinates nextStep = {start_x, start_y};
//     printf("Start: (%d, %d)\n", nextStep.x, nextStep.y);

//     while (!(nextStep.x == dest_x && nextStep.y == dest_y)) {
//         nextStep = DFS(map, &stack, dest_x, dest_y);
//         printf("Next step: (%d, %d)\n", nextStep.x, nextStep.y);
//     }

//     return 0;
// }



// int isValid(Map_t* map, int x, int y) {
//     if (x >= 0 && x < MAP_SIZE && y >= 0 && y < MAP_SIZE && 
//         map->tileArray[x][y] < STATUS_OBSTACLE_BY_USER) {

//         return 1;
//     }
//     return 0;
// }

// int dfs(Map_t* map, int agentLoc_x, int agentLoc_y, int endPointLoc_x, int endPointLoc_y) {
//     if (curVisited[agentLoc_x][agentLoc_y] == 1 || 
//         map->tileArray[agentLoc_x][agentLoc_y] >= STATUS_OBSTACLE_BY_USER) {
//         // curVisited or obstacle
//         return NO_FOUND;
//     }

//     path[pathIndex][0] = agentLoc_x;
//     path[pathIndex][1] = agentLoc_y;
//     pathIndex++;
//     pathLength++;
//     // printf("%d", pathIndex);
//     // for (int i = 0; i < pathLength; i++) {
//     //     printf("(%d, %d) ", path[i][0], path[i][1]);
//     // }
//     curVisited[agentLoc_x][agentLoc_y] = 1;

//     if (agentLoc_x == endPointLoc_x && 
//         agentLoc_y == endPointLoc_y) {
//         // printf("******");
//         int direction = NO_FOUND;
//         if (pathIndex > 1) {
//             direction = nextStep(path[pathIndex - 2][0], path[pathIndex - 2][1], 
//                                  path[pathIndex - 1][0], path[pathIndex - 1][1]);
//         }
//         pathIndex--;
//         return direction;
//     }

//     int minDistance = 100000;
//     int bestDirection = NO_FOUND;

//     for (int i = 0; i < 4; i++) {
//         int new_x = agentLoc_x + directions[i][0];
//         int new_y = agentLoc_y + directions[i][1];
//         // printf("%d %d", new_x, new_y);
//         if (new_x >= 0 && new_x < MAP_SIZE && new_y >= 0 && new_y < MAP_SIZE &&
//             curVisited[new_x][new_y] == 0 &&
//             map->tileArray[new_x][new_y] < STATUS_OBSTACLE_BY_USER) {
//             int distance = calculateDistance(new_x, new_y, endPointLoc_x, endPointLoc_y);
//             if (distance < minDistance) {
//                 curVisited[new_x][new_y] = 1; // Mark as curVisited
//                 if (dfs(map, new_x, new_y, endPointLoc_x, endPointLoc_y) != NO_FOUND) {
//                     // printf("****");
//                     minDistance = distance;
//                     bestDirection = nextStep(agentLoc_x, agentLoc_y, new_x, new_y);
//                     curVisited[new_x][new_y] = 0;
//                     break; // Finding only one path is enough
//                 }
//                 curVisited[new_x][new_y] = 0;
//             }
//         }
//     }

// return bestDirection; 
// }

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
//     int bestX = -1, bestY = -1;

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

//     if (bestX != -1 && dfsTest(map, bestX, bestY, endPointLoc_x, endPointLoc_y)) {
//         return 1;
//     }

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


// int dfsTest(Map_t* map, int agentLoc_x, int agentLoc_y, int endPointLoc_x, int endPointLoc_y) {
//     if (agentLoc_x == endPointLoc_x && agentLoc_y == endPointLoc_y) {
//         path[pathIndex][0] = agentLoc_x;
//         path[pathIndex][1] = agentLoc_y;
//         pathIndex++;
//         return 1;
//     }

//     curVisited[agentLoc_x][agentLoc_y] = 1;

//     for (int i = 0; i < MAP_SIZE; i++) {
//         printf("%2d ", i);
//         for (int j = 0; j < MAP_SIZE; j++) {
//             printf("%d", curVisited[i][j]);
//         }
//         printf("\n");
//     }
//     path[pathIndex][0] = agentLoc_x;
//     path[pathIndex][1] = agentLoc_y;


//     pathIndex++;

//     int closestDistance = INT32_MAX;
//     int nextStepIndex = -1;

//     for (int i = 0; i < 4; i++) {
//         int new_x = agentLoc_x + directions[i][0];
//         int new_y = agentLoc_y + directions[i][1];
//         if (isValid(map, new_x, new_y) && !curVisited[new_x][new_y]) {
//             int distance = calculateDistance(new_x, new_y, endPointLoc_x, endPointLoc_y);
//             if (distance < closestDistance) {
//                 closestDistance = distance;
//                 nextStepIndex = i;
//             }
//         }
//     }

//     if (nextStepIndex != -1) {
//         int new_x = agentLoc_x + directions[nextStepIndex][0];
//         int new_y = agentLoc_y + directions[nextStepIndex][1];
//         if (dfsTest(map, new_x, new_y, endPointLoc_x, endPointLoc_y)) {
//             return 1; 
//         }
//     }

//     pathIndex--;
//     curVisited[agentLoc_x][agentLoc_y] = 0;
//     return 0;
// }



// int dfsTest(Map_t* map, int agentLoc_x, int agentLoc_y, int endPointLoc_x, int endPointLoc_y) {
//     if (agentLoc_x == endPointLoc_x && agentLoc_y == endPointLoc_y) {
//         path[pathIndex][0] = agentLoc_x;
//         path[pathIndex++][1] = agentLoc_y;
//         return 1;
//     }

//     curVisited[agentLoc_x][agentLoc_y] = 1;
//     // for (int i = 0; i < MAP_SIZE; i++) {
//     //     printf("%2d ", i);
//     //     for (int j = 0; j < MAP_SIZE; j++) {
//     //         printf("%d", curVisited[i][j]);
//     //     }
//     //     printf("\n");
//     // }
//     // for (int i = 0; i < pathIndex; i++) {
//     //     printf("(%d, %d) ", path[i][0], path[i][1]);
//     // }
//     int distances[4];
//     int indexes[4];
//     int validDirections = 0;

//     for (int i = 0; i < 4; i++) {
//         int new_x = agentLoc_x + directions[i][0];
//         int new_y = agentLoc_y + directions[i][1];
//         if (isValid(map, new_x, new_y)) {
//             distances[validDirections] = calculateDistance(new_x, new_y, endPointLoc_x, endPointLoc_y);
//             indexes[validDirections++] = i;
//         }
//     }

//     if (validDirections == 0) {
//         curVisited[agentLoc_x][agentLoc_y] = 0;
//         return 0;
//     }

//     // shuffleDirections(distances, indexes, validDirections);

//     for (int i = 0; i < validDirections; i++) {
//         int idx = indexes[i];
//         int new_x = agentLoc_x + directions[idx][0];
//         int new_y = agentLoc_y + directions[idx][1];
//         if (dfsTest(map, new_x, new_y, endPointLoc_x, endPointLoc_y)) {
//             path[pathIndex][0] = agentLoc_x;
//             path[pathIndex++][1] = agentLoc_y;
//             return 1;
//         }
//     }

//     curVisited[agentLoc_x][agentLoc_y] = 0;
//     pathIndex--;
//     return 0;
// }
