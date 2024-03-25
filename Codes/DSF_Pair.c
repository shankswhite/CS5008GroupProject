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

typedef struct {
    Coordinates data[MAP_SIZE * MAP_SIZE]; // Maximum possible size
    int top;
} Stack;

typedef struct {
    Coordinates next_step;
    Coordinates ns;
} CoordinatePair;

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
CoordinatePair DFS(Map_t* map, Stack *stack, int dest_x, int dest_y) {
    Coordinates next_step;
    Coordinates ns;
    Coordinates current;
    current = pop(stack);

    int nx, ny;

    // Possible moves (down, right, up, left)
    int dx[] = {0, 1, 0, -1};
    int dy[] = {1, 0, -1, 0};

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
                push(stack, next_step);
                return (CoordinatePair){next_step, stack->data[stack->top]};
            }

            // Push the next step to the stack for further exploration
            push(stack, next_step);

            CoordinatePair result = {next_step, stack->data[stack->top]};
            return result; // Return the next step and ns to continue traversal in main
        }
    }
    // If no valid move found, return current position and ns
    return (CoordinatePair){current, stack->data[stack->top]};
}

int main() {
    // Initialize a map
    Map_t *map = (Map_t *) calloc(MAP_SIZE, sizeof(Map_t));
    updateMap(map, 0, 8, STATUS_OBSTACLE_BY_USER);
    updateMap(map, 1, 7, STATUS_OBSTACLE_BY_USER);
    updateMap(map, 2, 6, STATUS_OBSTACLE_BY_USER);
    updateMap(map, 5, 0, STATUS_OBSTACLE_BY_USER);
    updateMap(map, 4, 1, STATUS_OBSTACLE_BY_USER);
    updateMap(map, 3, 10, STATUS_OBSTACLE_BY_USER);
    updateMap(map, 4, 6, STATUS_OBSTACLE_BY_USER);
    updateMap(map, 4, 7, STATUS_OBSTACLE_BY_USER);
    updateMap(map, 4, 8, STATUS_OBSTACLE_BY_USER);
    updateMap(map, 2, 8, STATUS_OBSTACLE_BY_USER);
    updateMap(map, 3, 9, STATUS_OBSTACLE_BY_USER);

    // Set start and end points
    int start_x = 0;
    int start_y = 0;
    int dest_x = 19;
    int dest_y = 19;

    Stack stack;
    initialize(&stack);
    push(&stack, (Coordinates){start_x, start_y});

    CoordinatePair nextCall;
    nextCall.next_step.x = start_x;
    nextCall.next_step.y = start_y;
    while (!(nextCall.next_step.x == dest_x && nextCall.next_step.y == dest_y)) {
        printf("\n");
        nextCall = DFS(map, &stack, dest_x, dest_y);
        // Print the stack
        printf("Stack: ");
        for (int i = 0; i <= stack.top; ++i) {
            printf("(%d, %d) ", stack.data[i].x, stack.data[i].y);
        }
        printf("\n");
        printf("Next step: (%d, %d)\n", nextCall.ns.x, nextCall.ns.y);
        printf("\n");
    }
    return 0;
}
