#include "tests_world/tests_world.h"
#include <stdint.h>

#include "manager.h"
#include "map/map_manifest.h"
#include "map/map.h"

typedef TestCase_t TestCase_t;
typedef TestList_t TestList_t;


TestList_t testSection_World = {
    .length = 0,
    .list = {
        {&Test_LoadMapById, "LoadMapById"},
        {}
    }
};


uint32_t Test_LoadMapById(void){
    MapManifest_t manifest = {

    };
    uint32_t id;

    Map_t* actualResult = LoadMapById(&manifest, id); 
}


TestList_t* TestSection_World(void){
    return &testSection_World;
}
