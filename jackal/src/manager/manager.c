#include "manager.h"
#include "map/map_manifest.h"
#include "map/map.h"
#include <stdint.h>

/*  Manages engine internal game state
   
*/


Manager_t* InitManagement(void){
    Manager_t* newManager = malloc(sizeof(Manager_t));
    if(InitMapManifest()){
        // Crit err: no map data
        return NULL;
    }
    if(InitEntityManifest()){
        /* Crit err: no entity data */
        return NULL;
    }

    return newManager;
}


void LoadOrigins(Manager_t* manager){
    manager->currentMap = LoadMapByIndex(manager->originMap);
    manager->currentEntities = LoadEntityList(manager->originEntity);
}

