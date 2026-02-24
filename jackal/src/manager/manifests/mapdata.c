#include "mapdata.h"
#include "floader.h"
#include "manager.h"
#include "parsing.h"
#include <stdlib.h>




static inline uint8_t ParseKey(MapKey_t* key, uint8_t** src, size_t* size){
    if (*size < MAP_KEY_SIZE){
        return 1;
    }

    CopyData(&key->length, sizeof(key->length), src, size);
    CopyData(&key->width,  sizeof(key->width),  src, size);
    CopyData(&key->flags,  sizeof(key->flags),  src, size);
    CopyData(&key->offset, sizeof(key->offset), src, size);
    CopyData(&key->size,   sizeof(key->size),   src, size);

    return 0;
}

static inline void ParseMapIndex(MapIndex_t* map, uint8_t* src){
    int i = 0;
    memcpy(map->length, )
}



void ParseMapManifest(MapManifest_t* world){
    struct fileData {
        uint8_t* bufferPtr;
        size_t bufferSize;
    };
    uint8_t* bufferPtr;
    size_t dataSize = GetFileData(&bufferPtr, MANIFEST_DIR_PATH, MAP_FNAME);
    
    uint8_t* srcPtr = *bufferPtr;
    uint32_t nKeys = ParseHeader(&srcPtr, &dataSize);

    if(!nKeys || dataSize < (size_t)(nKeys * MAP_KEY_SIZE)){
        return; // TODO: handle error
    }



    MapKey_t* mapKeys = malloc(nKeys * sizeof(MapKey_t));
    for (int i = 0; i < nKeys; i++){
        if (ParseKey(&mapKeys[i], &bufferPtr, &dataSize)){
            break;
        }
        world->mapCount++;
    }
    world->mapKeys = mapKeys;
    free(bufferPtr);
}

MapManifest_t* GetMapManifest(void){
    uint8_t* buffPtr;
    size_t srcSize = GetFileData(&buffPtr, MANIFEST_DIR_PATH, MAP_FNAME);
    if (srcSize < FILE_HEADER_SIZE){
        return NULL;
    }

    uint8_t* src = *buffPtr;
    uint32_t indexs = ParseHeader(&src, &srcSize);
    if (indexs == 0){
        return NULL;
    }
    MapManifest_t* manifest = malloc(sizeof(MapManifest_t));
    MapIndex_t* mapArray = malloc(sizeof(MapIndex_t) * indexs);
    manifest->manifest = &mapArray;

    for (int i = 0; i < indexs; i++){
        ParseMapIndex();
        manifest->length++;
    }

    return manifest;
}