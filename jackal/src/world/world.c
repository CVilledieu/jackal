#include "world.h"
#include <stdlib.h>
#include <string.h>

#define WORLD_PATH "assets\\world\\"

/*
    World component system is made of 3 sub systems
    - Terrain system
        -
    - Entity system
    - Currently unnamed system
*/


void ParseMapHeader(World_t* wd){
    uint8_t* bufferPtr;
    size_t dataSize = GetFileData(&bufferPtr, WORLD_PATH, "maps.jpup");

    uint32_t mapCount;
    memcpy(&mapCount, bufferPtr, sizeof(uint32_t));
}


World_t* CreateWorld(void){
    World_t* world = malloc(sizeof(World_t));

    world->currentMap = NULL;
    world->mapCount = 0;


    ParseMapHeader(world);

    return world;
}


Terrain_t* LoadMap(World_t* world, uint32_t mapIndex) {
    MapPage_t* guide = &world->mapGuide[mapIndex];
    // You already know the size and offset — one targeted read
    uint8_t* data = LoadRegion(guide->offset, guide->size);
    return BuildTerrain(data, guide->width, guide->length);
}