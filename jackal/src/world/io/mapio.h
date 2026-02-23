#ifndef __MAP_IO_H__
#define __MAP_IO_H__

#include <stdint.h>


typedef struct MapKey_t{
    uint16_t width;
    uint16_t length;
    uint32_t flags;
    uint32_t offset;
    uint32_t size;
} MapKey_t;

#define MAP_KEY_SIZE 16

typedef struct World_t World_t;

void ParseMap(World_t* wd);


#endif