#include "realm.h"
#include "map/map_manifest.h"
#include "map/map.h"
#include <stdint.h>

/*  Manages engine internal game state
   
*/


Realm_t* NewRealm(void){
    Realm_t* newRealm = malloc(sizeof(Realm_t));

    InitMapManifest();
    InitEntityManifest();

    return newRealm;
}


void LoadOrigins(Realm_t* realm){
    realm->currentMap = LoadMapByIndex(realm->originMap);
    realm->currentEntities = LoadEntityList(realm->originEntity);
}

