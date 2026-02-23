#ifndef __MAP_PARSER_H__
#define __MAP_PARSER_H__

#include <stdint.h>


typedef struct MapHeader_t{
    uint32_t signature;
    uint32_t version;
    uint32_t nKeys;
} MapHeader_t;

#define MAP_HEADER_SIZE sizeof(MapHeader_t)

typedef struct MapKey_t{
    uint16_t width;
    uint16_t length;
    uint32_t flags;
    uint32_t offset;
    uint32_t size;
} MapKey_t;

#define MAP_KEY_SIZE sizeof(MapKey_t)

typedef struct World_t World_t;

void ParseMap(World_t* wd);


#endif