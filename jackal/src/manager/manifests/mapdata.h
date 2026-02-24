#ifndef __MAP_DATA_H__
#define __MAP_DATA_H__

#include <stdint.h>

#define MAP_FNAME "mapKeys.jpup"

typedef struct MapKey_t{
    uint16_t width;
    uint16_t length;
    uint32_t flags;
    uint32_t offset;
    uint32_t size;
} MapKey_t;

typedef struct MapIndex_t{
    uint16_t width;
    uint16_t length;
} MapIndex_t;

typedef struct MapManifest_t{
    MapIndex_t* manifest;
    uint32_t length;
} MapManifest_t;

#define MAP_KEY_SIZE 16




#endif