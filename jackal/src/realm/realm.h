#pragma once

#include "types.h"
#include <stdint.h>

#define MANIFEST_DIR_PATH "assets\\stage\\"


/* Call aheads */
typedef struct Map_t Map_t;
typedef struct Entities_t Entities_t;
typedef struct MapManifest_t MapManifest_t;
typedef struct EntityManifest_t EntityManifest_t;

typedef struct Realm_t{
    uint32_t originMap;
    uint32_t originEntity;

    Map_t* currentMap;
    Entities_t* currentEntities;

    MapManifest_t* mapList;
    EntityManifest_t* entityList;

} Realm_t;



Realm_t* NewRealm(void);
void LoadOrigins(Realm_t* realm);