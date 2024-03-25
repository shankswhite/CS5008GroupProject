#ifndef LEVEL_H
#define LEVEL_H

#include "map.h"

Map_t createLevel1(); // for test matrix
Map_t createLevel2(); // for test UI
Map_t createLevel3(); // for test flood fill
Map_t createLevel4(); // for test dfs

extern int g_agent_locx;
extern int g_agent_locy;
extern int g_endPoint_locx;
extern int g_endPoint_locy;

#endif
