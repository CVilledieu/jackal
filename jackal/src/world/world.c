#include "world.h"
#include "parsers/map_parser.h"
#include <stdlib.h>
#include <string.h>

/*
    World component system is made of 3 sub systems
    - Terrain system
        -
    - Entity system
    - Currently unnamed system 
*/




World_t* CreateWorld(void){
    World_t* world = malloc(sizeof(World_t));

    world->currentMap = NULL;
    world->mapCount = 0;


    ParseMapHeader(world);

    return world;
}


Terrain_t* LoadMap(World_t* world, uint32_t mapIndex) {
    MapKey_t* page = &world->mapKeys[mapIndex];
    // You already know the size and offset — one targeted read
    uint8_t* data = LoadRegion(page->offset, page->size);
    return BuildTerrain(data, page->width, page->length);
}