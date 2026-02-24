#include "map_manifest.h"
#include "floader.h"
#include "manager.h"
#include "parsing.h"
#include <stdlib.h>




static inline uint8_t ParseMapRecord(MapRecord_t* record, uint8_t** src, size_t* size){
    if (*size < MAP_RECORD_SIZE){
        return 1;
    }
    size_t index = 0;
    memcpy(record->id, src[index], sizeof(record->id));
    index += sizeof(record->id);
    memcpy(record->length, src[index], sizeof(record->length));
    memcpy(record->)
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
    manifest->table = malloc(sizeof(MapRecord_t) * indexs);


    for (int i = 0; i < indexs; i++){
        ParseMapRecord();
        manifest->length++;
    }

    return manifest;
}