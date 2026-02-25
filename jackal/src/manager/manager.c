#include "manager.h"
#include "manifests/map_manifest.h"
#include "manifests/entity_manifest.h"
#include <stdlib.h>
#include <string.h>

/* State manager 
*/



Manager_t* CreateManagement(void){
    Manager_t* newManager = malloc(sizeof(Manager_t));
    if(GetMapManifest()){
        return NULL;
    }    

    return newManager;
}


