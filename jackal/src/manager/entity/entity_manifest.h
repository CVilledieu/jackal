#pragma once

#include <stdint.h>

typedef struct EntityRecords_t{
    uint32_t id;
    uint32_t flags;
} EntityRecords_t;

typedef struct EntityManifest_t{
    EntityRecords_t* table;
    uint32_t length;
} EntityManifest_t;