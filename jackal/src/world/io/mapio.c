#include "mapio.h"
#include "floader.h"
#include "world/world.h"
#include "parsing.h"
#include <stdlib.h>


static inline MapKey_t* NewMapKey(void){
    MapKey_t* key = malloc(sizeof(MapKey_t));
    key->length = 0;
    key->width  = 0;
    key->offset = 0;
    key->size   = 0;
    key->flags  = 0;
    return key;
}



static inline MapKey_t* ParseMapKey(uint8_t** src, size_t* size){
    if (*size < MAP_KEY_SIZE){
        return NULL;
    }
    MapKey_t* key = NewMapKey();

    CopyData(&key->length, sizeof(key->length), src, size);
    CopyData(&key->width,  sizeof(key->width),  src, size);
    CopyData(&key->flags,  sizeof(key->flags),  src, size);
    CopyData(&key->offset, sizeof(key->offset), src, size);
    CopyData(&key->size,   sizeof(key->size),   src, size);

    return key;
}


void ParseMap(World_t* world){
    uint8_t* bufferPtr;
    size_t dataSize = GetFileData(&bufferPtr, WORLD_FPATH, MAP_FNAME);
    uint8_t* srcPtr = *bufferPtr;
    FileHeader_t* header = ParseHeader(&bufferPtr, &srcPtr);
    if(header == NULL){
        return; // TODO: handle error
    }

    if(dataSize < (size_t)(header->nKeys * MAP_KEY_SIZE)){
        return; // TODO: handle error
    }

    world->mapKeys = calloc(header->nKeys, sizeof(MapKey_t*));
    for (int i = 0; i < header->nKeys; i++){
        world->mapKeys[i] = ParseMapKey(&bufferPtr, &dataSize);
        if (world->mapKeys[i] == NULL){

        }
    }
    free(header);
}