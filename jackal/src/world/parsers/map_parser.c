#include "map_parser.h"
#include "floader.h"
#include "world/world.h"
#include <string.h>

const uint32_t FILE_SIGNATURE = 0;
const uint32_t FILE_VERSION = 0; 
#define MAP_FNAME "maps.jpup"

static inline MapKey_t* NewMapKey(void){
    MapKey_t* key = malloc(sizeof(MapKey_t));
    key->length = 0;
    key->width  = 0;
    key->offset = 0;
    key->size   = 0;
    key->flags  = 0;
    return key;
}

static inline size_t CopyData(void* dest, size_t dSize, uint8_t** src, size_t sSize){
    if(sSize < dSize){
        return 0;
    }
    memcpy(dest, *src, dSize);
    *src += dSize;

    return (sSize - dSize);
}


static inline MapKey_t* ParseMapKey(uint8_t** src, size_t* size){
    if (size < MAP_KEY_SIZE){
        return NULL;
    }
    MapKey_t* key = NewMapKey();
    
    size_t remainingSize = MAP_KEY_SIZE;

    CopyData(&key->length, sizeof(uint16_t), &src, &remainingSize);
    CopyData(&key->width, sizeof(uint16_t), &src, remainingSize);

    return key;
}

static inline uint32_t ParseMapHeader(uint8_t* src, size_t* size){
    uint32_t signature;
    *size = CopyData(&signature, sizeof(uint32_t), &src, *size);

    uint32_t version;
    *size = CopyData(&version, sizeof(uint32_t), &src, *size);
    if (version != FILE_VERSION || signature != FILE_SIGNATURE){
        return 0;
    }
    uint32_t pages;
    *size = CopyData(&pages, sizeof(uint32_t), &src, *size);
    
    return pages;
}


void ParseMap(World_t* wd){
    uint8_t* bufferPtr;
    size_t dataSize = GetFileData(&bufferPtr, WORLD_FPATH, MAP_FNAME);

    uint32_t pageCount = ParseMapHeader(bufferPtr, &dataSize);
    if(!pageCount){
        return; // TODO: handle error
    }




}