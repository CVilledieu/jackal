#include "manager.h"
#include "map/map_manifest.h"
#include "map/map.h"
#include <stdint.h>

/* State manager 
*/

#define ORIGIN_MAP_ID 0

Manager_t* InitManagement(void){
    Manager_t* newManager = malloc(sizeof(Manager_t));
    if(InitMapManifest()){
        // Crit err: no map data
        return NULL;
    }

    newManager->currentMap = LoadMapByIndex((uint32_t)ORIGIN_MAP_ID);


    return newManager;
}


