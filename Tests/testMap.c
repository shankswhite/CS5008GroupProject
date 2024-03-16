
// gcc -o testMap Tests/testMap.c Codes/map.c Codes/level.c -ICodes

#include <stdio.h>  // For IO operations
#include <stdlib.h> // for malloc/free

// Our library that we have written.
// Also, by a really smart engineer!
#include "../Codes/map.h"
#include "../Codes/level.h"
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
    Map_t testLevel = createLevel1();
    Map_t* testMap = newMap(testLevel);
    if (testMap->tileArray[0][0] == 1 && testMap->tileArray[19][19] == 2) {
        passed = 1;
    }

    printMap(testMap);

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
