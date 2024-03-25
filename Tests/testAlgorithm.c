
// gcc -o testMap Tests/testMap.c Codes/map.c Codes/level.c -ICodes

#include <stdio.h>  // For IO operations
#include <stdlib.h> // for malloc/free

// Our library that we have written.
// Also, by a really smart engineer!
#include "../Codes/map.h"
#include "../Codes/level.h"
#include "../Codes/agent.h"
#include "../Codes/gameLogic.h"
// #include "../Codes/dfs.c"
// Note that we are locating this file
// within the same directory, so we use quotations
// and provide the path to this file which is within
// our current directory.


// A sample collection of tests for your program
// You can add as many unit tests as you like
// We will be adding our own to test your program.


// Tests creation and deletion of the hashmap
// Ideally does not cause any segfaults, and this
// is considered passing.
int unitTest1(int status) {
    // initial map
    int passed = 0;
    Map_t testLevel = createLevel3();
    Map_t* testMap = newMap(testLevel);

    printMap(testMap);
    printf("\n");

    int start_x = 0;
    int start_y = 1;
    int dest_x = 19;
    int dest_y = 19;

    Stack stack;
    initialize(&stack);
    push(&stack, (Coordinates){start_x, start_y});

    Coordinates nextStep = {start_x, start_y};
    printf("Start: (%d, %d)\n", nextStep.x, nextStep.y);

    while (!(nextStep.x == dest_x && nextStep.y == dest_y)) {
        nextStep = dfsTest3(testMap, &stack, dest_x, dest_y);
        printf("Next step: (%d, %d)\n", nextStep.x, nextStep.y);
    }
    // for (int j = 0; j < MAP_SIZE; j++) {
    //     printf("(%d, %d)", path[j][0], path[j][1]);
    // }
    // printf("\n");
    
    // printf("%d \n", findPath(9, 19, 19, 19, testMap, ));
    // for (int i = 0; i < MAP_SIZE; i++) {
    //     printf("%2d ", i);
    //     for (int j = 0; j < MAP_SIZE; j++) {
    //         printf("%d", curVisited[i][j]);
    //     }
    //     printf("\n");
    // }
    printf("stuck ? >%d", checkStuck(0, 1, 19, 19, testMap));
    printf("\n");

    // printf("daozhe");
    // dfsTest2(testMap, start, end);



    // printf("find ? >%d", findPath(0, 1, 19, 19, testMap));
    printf("\n");
    freeMap(testMap);
    return passed;
}

int (*unitTests[])(int)={
    unitTest1,

    NULL
};

// ====================================================
// ================== Program Entry ===================
// ====================================================
int main() {
    unsigned int testsPassed = 0;
    // List of Unit Tests to test your data structure
    int counter =0;
    while(unitTests[counter]!=NULL){
	printf("========unitTest %d========\n", counter);
        if(1==unitTests[counter](1)){
		printf("passed test\n");
		testsPassed++;	
	}else{
		printf("failed test, missing functionality, or incorrect test\n");
	}
        counter++;
    }

    printf("%d of %d tests passed\n", testsPassed, counter);

    return 0;
}
