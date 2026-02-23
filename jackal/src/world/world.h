#ifndef __WORLD_SYS_H__
#define __WORLD_SYS_H__

#include "types.h"
#include <stdint.h>

#define WORLD_FPATH "assets\\world\\"


typedef struct Terrain_t Terrain_t;
typedef struct MapPage_t MapPage_t;


typedef struct World_t{
    MapKey_t** mapKeys;
    uint32_t mapCount;

    Terrain_t* currentMap;
} World_t;


#endif