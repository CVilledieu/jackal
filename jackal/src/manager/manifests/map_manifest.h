#pragma once

#include <stdint.h>

#define MAP_RECORD_SIZE 16
#define MAP_FNAME "map_records.jkp"



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




