#ifndef __WORLD_SYS_H__
#define __WORLD_SYS_H__

#include "types.h"
#include <stdint.h>


/* Map file schema
    - signature [4 bytes]
    - version   [4 bytes]
    - pageCount [4 bytes]
*/
#define MAP_HEADER_SIZE 12
/*
    mapPage schema
    - length [2 bytes]
    - width  [2 bytes]
    - flags  [2 bytes] 
    - offset [4 bytes]
    - size   [4 bytes]
*/  
#define MAP_SCHEMA_SIZE 44


typedef struct Terrain_t Terrain_t;

typedef struct MapPage_t{
    uint16_t width;
    uint16_t length;
    uint32_t offset;
    uint32_t size;

} MapPage_t;


typedef struct World_t{
    MapPage_t* mapGuide;
    uint32_t mapCount;

    Terrain_t* currentMap;
} World_t;


#endif