#ifndef LEVEL_H
#define LEVEL_H

#include "map.h"
#include "agent.h"

Map_t createLevel1(); // for test matrix
Map_t createLevel2(); // for test UI
Map_t createLevel3(); // for test flood fill
Map_t createLevel4(); // for test dfs
Map_t createLevel5(); // for test dfs boundary case

#define START_X 0
#define START_Y 1
#define END_X 19
#define END_Y 19

extern int g_agent_locx;
extern int g_agent_locy;
extern int g_endPoint_locx;
extern int g_endPoint_locy;
extern Coordinates START_COORDINATE;

#endif
