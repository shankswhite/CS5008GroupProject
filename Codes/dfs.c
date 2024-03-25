// #include "map.h"
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include "level.h"

// typedef struct {
//     int x;
//     int y;
// } Coordinates;

// typedef struct {
//     Coordinates data[MAP_SIZE * MAP_SIZE]; // Maximum possible size
//     int top;
// } Stack;

// void initialize(Stack *stack) {
//     stack->top = -1;
// }

// int isEmpty(Stack *stack) {
//     return stack->top == -1;
// }

// void push(Stack *stack, Coordinates item) {
//     if (stack->top == MAP_SIZE * MAP_SIZE - 1) {
//         printf("Stack overflow\n");
//         return;
//     }
//     stack->data[++stack->top] = item;
// }

// Coordinates pop(Stack *stack) {
//     if (isEmpty(stack)) {
//         printf("Stack underflow\n");
//         exit(1);
//     }
//     return stack->data[stack->top--];
// }

// // DFS algorithm to find the shortest path
// Coordinates DFS(Map_t* map, Stack *stack, int dest_x, int dest_y) {
//     Coordinates next_step;
//     Coordinates current;
//     current = pop(stack);

//     int nx, ny;

//     // Possible moves (right, down, left, up)
//     int dx[] = {1, 0, -1, 0};
//     int dy[] = {0, 1, 0, -1};

//     for (int i = 0; i < 4; ++i) {
//         nx = current.x + dx[i];
//         ny = current.y + dy[i];

//         // Check if the next move is within bounds and not an obstacle
//         if (nx >= 0 && nx < MAP_SIZE && ny >= 0 && ny < MAP_SIZE &&
//             tileStatus(map, nx, ny) != STATUS_OBSTACLE_BY_USER &&
//             tileStatus(map, nx, ny) != STATUS_OBSTACLE_BY_DEFAULT &&
//             tileStatus(map, nx, ny) != STATUS_AGENT_PAST) {

//             // Move to the next location
//             next_step.x = nx;
//             next_step.y = ny;
//             updateMap(map, nx, ny, STATUS_AGENT_PAST);
//             push(stack, current);

//             // Check if the destination is reached
//             if (nx == dest_x && ny == dest_y) {
//                 return next_step;
//             }

//             // Push the next step to the stack for further exploration
//             push(stack, next_step);
//             return next_step; // Return the next step to continue traversal in main
//         }
//     }

//     // If no valid move found, return current position
//     return current;
// }

// // int main() {
// //     // Initialize a map
// //     Map_t testLevel = createLevel3();
// //     Map_t* map = newMap(testLevel);

// //     printf("Status of tile at position (4, 0): %d\n", tileStatus(map, 4, 0));

// //     // Set start and end points
// //     int start_x = 0;
// //     int start_y = 1;
// //     int dest_x = 19;
// //     int dest_y = 19;

// //     Stack stack;
// //     initialize(&stack);
// //     push(&stack, (Coordinates){start_x, start_y});

// //     Coordinates nextStep = {start_x, start_y};
// //     printf("Start: (%d, %d)\n", nextStep.x, nextStep.y);

// //     while (!(nextStep.x == dest_x && nextStep.y == dest_y)) {
// //         nextStep = DFS(map, &stack, dest_x, dest_y);
// //         printf("Next step: (%d, %d)\n", nextStep.x, nextStep.y);
// //     }

// //     return 0;
// // }