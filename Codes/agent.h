#define NO_FOUND 0
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4


extern int path[MAP_SIZE * MAP_SIZE][2];
extern int pathIndex;
extern int pathLength;
extern int curVisited[MAP_SIZE][MAP_SIZE];

typedef int (*PathFindingAlgorithmPointer)(Map_t* map, int agentLoc_x, int agentLoc_y, int endPointLoc_x, int endPointLoc_y);


int agentNextMove(PathFindingAlgorithmPointer pfaP, Map_t* map, int agentLoc_x, int agentLoc_y, int endPointLoc_x, int endPointLoc_y);
int dfs(Map_t* map, int agentLoc_x, int agentLoc_y, int endPointLoc_x, int endPointLoc_y);
int dfsTest(Map_t* map, int agentLoc_x, int agentLoc_y, int endPointLoc_x, int endPointLoc_y);
int findPath(int x, int y, int endX, int endY, Map_t* map);

// void updateMapAgent(Map_t* map, int agentLoc_x, int agentLoc_y);