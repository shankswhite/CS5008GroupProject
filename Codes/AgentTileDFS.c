#include "map.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent the agent's position
typedef struct Agent {
    int x;
    int y;
} Agent_t;

// Function to initialize the agent at the start point
Agent_t* initAgent(int start_x, int start_y) {
    Agent_t* agent = (Agent_t*)malloc(sizeof(Agent_t));
    if (agent == NULL) {
        return NULL;
    }
    agent->x = start_x;
    agent->y = start_y;
    return agent;
}

// DFS algorithm to find the shortest path
int* DFS(Map_t* map, Agent_t* agent, int dest_x, int dest_y) {
    int x = agent->x;
    int y = agent->y;

    // If the current location is the destination, return NULL
    if (x == dest_x && y == dest_y) {
        return NULL;
    }

    // Mark current location as visited
    updateMap(map, x, y, AGENT_PAST_LOCATION);

    // Possible moves (up, down, left, right)
    int dx[] = {0, 0, -1, 1};
    int dy[] = {-1, 1, 0, 0};

    for (int i = 0; i < 4; ++i) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        // Check if the next move is within bounds and not an obstacle
        if (nx >= 0 && nx < MAP_SIZE && ny >= 0 && ny < MAP_SIZE &&
            tileStatus(map, nx, ny) != OBSTACLE_USER && tileStatus(map, nx, ny) != OBSTACLE_DEFAULT) {

            // Check if the next move has not been visited
            if (tileStatus(map, nx, ny) != AGENT_PAST_LOCATION) {
                // Move to the next location
                agent->x = nx;
                agent->y = ny;

                // Recursively explore from the next location
                int* next_move = DFS(map, agent, dest_x, dest_y);

                // If the destination is found, return NULL
                if (next_move != NULL) {
                    return next_move;
                }

                // If the destination is not found, return the coordinates of the next move
                int* next_tile = malloc(2 * sizeof(int));
                next_tile[0] = nx;
                next_tile[1] = ny;
                return next_tile;
            }
        }
    }

    // Return NULL if no valid move is found
    return NULL;
}

int main() {
    // Initialize map and agent
    Map_t level;
    // Assuming start and win points are known
    int start_x = 0;
    int start_y = 0;
    int win_x = 5;
    int win_y = 5;

    Agent_t* agent = initAgent(start_x, start_y);

    // Perform DFS to find the shortest path
    int* next_move = DFS(&level, agent, win_x, win_y);

    // Output the coordinates of the next move
    if (next_move != NULL) {
        printf("Next move coordinates: (%d, %d)\n", next_move[0], next_move[1]);
        free(next_move);
    } else {
        printf("Destination reached.\n");
    }

    // Free memory
    freeMap(&level);
    free(agent);

    return 0;
}
