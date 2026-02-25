#pragma once

#include "types.h"
#include <stdint.h>

#define MANIFEST_DIR_PATH "assets\\stage\\"




typedef struct Manager_t{
    Map_t* currentMap;
    Entities_t* currentEntities;
} Manager_t;



Manager_t* CreateManagement(void);