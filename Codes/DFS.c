#include "map.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAP_SIZE 20
#define STATUS_NULL 0
#define STATUS_START 1
#define STATUS_END 2
#define STATUS_AGENT_CURR 3
#define STATUS_AGENT_PAST 4
#define STATUS_OBSTACLE_BY_USER 5
#define STATUS_OBSTACLE_BY_DEFAULT 6
typedef struct {
    int x;
    int y;
} Coordinates;

// DFS algorithm to find the shortest path
Coordinates DFS(Map_t* map, int start_x, int start_y, int dest_x, int dest_y) {
    Coordinates next_step;
    Coordinates current;
    Coordinates prev;
    current.x = start_x;
    current.y = start_y;

    int nx, ny;

    // If the current location is the destination, return NULL
    if (current.x == dest_x && current.y == dest_y) {
        return current;
    }

    updateMap(map, current.x, current.y, STATUS_AGENT_PAST);
    // Possible moves (right, down, left, up)
    int dx[] = {1, 0, -1, 0};
    int dy[] = {0, 1, 0, -1};

//    if (dest_x > current.x && dest_y > current.y) {
//        int temp = dx[0];
//        dx[0] = dx[1];
//        dx[1] = temp;
//        temp = dy[0];
//        dy[0] = dy[1];
//        dy[1] = temp;
//    }


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
                current.x = nx;
                current.y = ny;
                updateMap(map, nx, ny, STATUS_AGENT_PAST);
                return next_step;
            }
        prev.x = nx-dx[i];
        prev.y = nx-dy[i];
        }
    // Backtrack to the previous position
    updateMap(map, prev.x,prev.y, STATUS_NULL);
    next_step.x = prev.x;
    next_step.y = prev.y;
    return next_step;
}



    int main() {
        // Initialize a map
        Map_t *map = (Map_t *) calloc(MAP_SIZE, sizeof(Map_t));
        updateMap(map, 0, 8, STATUS_OBSTACLE_BY_USER);
        //updateMap(map, 0, 1, STATUS_OBSTACLE_BY_USER);
        updateMap(map, 1, 7, STATUS_OBSTACLE_BY_USER);
        updateMap(map, 2, 6, STATUS_OBSTACLE_BY_USER);
        updateMap(map, 5, 0, STATUS_OBSTACLE_BY_USER);
        updateMap(map, 4, 1, STATUS_OBSTACLE_BY_USER);
        printf("Status of tile at position (4, 0): %d\n", tileStatus(map, 4, 0));

        // Status of tile at position (3, 0)
        printf("Status of tile at position (3, 0): %d\n", tileStatus(map, 3, 0));

        // Status of tile at position (3, 1)
        printf("Status of tile at position (3, 1): %d\n", tileStatus(map, 3, 1));
        // Set start and end points
        int start_x = 0;
        int start_y = 0;
        int dest_x = 19;
        int dest_y = 19;

        Coordinates nextStep = {start_x, start_y};
        printf("Start: (%d, %d)\n", nextStep.x, nextStep.y);
        nextStep = DFS(map, nextStep.x, nextStep.y, dest_x, dest_y);
        printf("Next step: (%d, %d)\n", nextStep.x, nextStep.y);
        nextStep = DFS(map, nextStep.x, nextStep.y, dest_x, dest_y);
        printf("Next step: (%d, %d)\n", nextStep.x, nextStep.y);
        nextStep = DFS(map, nextStep.x, nextStep.y, dest_x, dest_y);
        printf("Next step: (%d, %d)\n", nextStep.x, nextStep.y);
        nextStep = DFS(map, nextStep.x, nextStep.y, dest_x, dest_y);
        printf("Next step: (%d, %d)\n", nextStep.x, nextStep.y);
        nextStep = DFS(map, nextStep.x, nextStep.y, dest_x, dest_y);

       // updateMap(map,3,0,0);

        printf("Next step: (%d, %d)\n", nextStep.x, nextStep.y);
        nextStep = DFS(map, nextStep.x, nextStep.y, dest_x, dest_y);
        printf("Next step: (%d, %d)\n", nextStep.x, nextStep.y);
        nextStep = DFS(map, nextStep.x, nextStep.y, dest_x, dest_y);
        printf("Next step: (%d, %d)\n", nextStep.x, nextStep.y);
        nextStep = DFS(map, nextStep.x, nextStep.y, dest_x, dest_y);
        printf("Next step: (%d, %d)\n", nextStep.x, nextStep.y);

        printf("Status of tile at position (4, 0): %d\n", tileStatus(map, 4, 0));

        // Status of tile at position (3, 0)
        printf("Status of tile at position (3, 0): %d\n", tileStatus(map, 3, 0));

        // Status of tile at position (3, 1)
        printf("Status of tile at position (3, 1): %d\n", tileStatus(map, 3, 1));
        while (!(nextStep.x == dest_x && nextStep.y == dest_y)) {
            nextStep = DFS(map, nextStep.x, nextStep.y, dest_x, dest_y);
            printf("Next step: (%d, %d)\n", nextStep.x, nextStep.y);
        }

        // Free the memory allocated for the map
        freeMap(map);

        return 0;
    }


