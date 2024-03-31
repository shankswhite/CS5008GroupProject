# for testing

all :
	gcc -o Tests/testMap Tests/testMap.c Codes/map.c Codes/level.c -ICodes
	gcc -o Tests/testAlgorithm Tests/testAlgorithm.c Codes/map.c Codes/gameLogic.c Codes/level.c Codes/agent.c -lm -ICodes
