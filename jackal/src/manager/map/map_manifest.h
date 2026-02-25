#pragma once

#include <stdint.h>
typedef struct Map_t Map_t;


#define MAP_RECORD_SIZE 64



typedef struct MapRecord_t{
    uint32_t id;
    uint16_t width;
    uint16_t length;
    uint32_t flags;
    uint8_t nameLength;
    uint8_t reserved;
    char fileName[48];
} MapRecord_t;

typedef struct MapManifest_t{
    MapRecord_t* table;
    uint32_t length;
} MapManifest_t;

uint8_t GetMapManifest(void);

Map_t* CreateNewMap(MapRecord_t* record);

void FreeMapManifest(void);