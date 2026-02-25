#include "map_manifest.h"
#include "floader.h"
#include "manager.h"
#include "parsing.h"
#include "map/map.h"
#include <stdlib.h>
#include <stdio.h>

#define MANIFEST_FILE "map_manifest.jkp"
#define FILE_PREFIX "map_"
#define FILE_EXTEN ".jkp"
#define ID_MAX_LENGTH 3
// 4 For prefix, 3 for map id, 4 for exten, 1 for null term
#define FNAME_MAX_LENGTH (sizeof(FILE_PREFIX) + ID_MAX_LENGTH + sizeof(FILE_EXTEN))

MapManifest_t* mapManifest = NULL;

static inline uint8_t ParseMapRecord(MapRecord_t* record, uint8_t** src, size_t* size){
    if (*size < MAP_RECORD_SIZE){
        return 1;
    }
    int nPairs = 7;
    ManifestField_t field[] = {
        {.fieldPtr = &record->id, .length = sizeof(record->id)},
        {.fieldPtr = &record->width, .length = sizeof(record->width)},
        {.fieldPtr = &record->length, .length = sizeof(record->length)},
        {.fieldPtr = &record->flags, .length = sizeof(record->flags)},
        {.fieldPtr = &record->nameLength, .length = sizeof(record->nameLength)},
        {.fieldPtr = &record->reserved, .length = sizeof(record->reserved)},
        {.fieldPtr = &record->fileName, .length = sizeof(record->fileName)},
        
    };
    for (int i = 0; i < nPairs; i++){
        size_t fieldSize = field[i].length;
        if (fieldSize == 1 || fieldSize == 2 || fieldSize == 4 || fieldSize == 8){
            if (ReadLEField(field[i].fieldPtr, fieldSize, src, size)){
                return 1;
            }
        }
        else {
            if (ReadBytes(field[i].fieldPtr, fieldSize, src, size)){
                return 1;
            }
        }
    } 

    return 0;
}



uint8_t GetMapManifest(void){
    uint8_t* buffPtr;
    size_t srcSize = GetFileData(&buffPtr, MANIFEST_DIR_PATH, MANIFEST_FILE);
    if (srcSize < HEADER_SIZE){
        return 1;
    }

    uint8_t* src = buffPtr;
    uint32_t indexs = ParseHeader(&src, &srcSize);
    if (indexs == 0){
        return 1;
    }
    
    mapManifest->length = 0;
    mapManifest->table = malloc(sizeof(MapRecord_t) * indexs);


    for (int i = 0; i < indexs; i++){
        if(ParseMapRecord(&mapManifest->table[i], &src, &srcSize)){
            break;
        }
        mapManifest->length++;
    }

    return 0;
}

static inline uint8_t ParseBlockData(uint16_t* dest, uint8_t* src, size_t* srcSize){
    if (*srcSize < (CHUNK_AREA * sizeof(uint16_t))){
        return 1;
    }
    for(int i = 0; i < CHUNK_AREA; i++){
        if(ReadLEField(&dest[i], sizeof(dest[i]), &src, srcSize)){
            return 1;
        }
    }
    return 0;
}



Map_t* LoadMapByIndex(uint32_t index){
    if (index >= mapManifest->length){
        return 1;
    }

    MapRecord_t* record = &mapManifest->table[index];
    Map_t* dest = NewMap(record);

    char fName[FNAME_MAX_LENGTH];
    snprintf(fName,FNAME_MAX_LENGTH, "%s%s%s", FILE_PREFIX, record->id, FILE_EXTEN);

    uint8_t* src;
    size_t srcSize = GetFileData(&src, MANIFEST_DIR_PATH, fName);
    uint32_t tempChunkCount = 0;
    if(ReadLEField(&tempChunkCount,sizeof(tempChunkCount), &src, srcSize)){
        return NULL;
    }

    dest->chunkList = malloc(sizeof(Chunk_t) * tempChunkCount);
    for (int i = 0; i < tempChunkCount; i++){
        Chunk_t* newChunk = &dest->chunkList[i];
        ReadLEField(&newChunk->coord.x, sizeof(newChunk->coord.x), &src, srcSize);
        ReadLEField(&newChunk->coord.z, sizeof(newChunk->coord.z), &src, srcSize);
        ParseBlockData(newChunk->blockIds, src, srcSize);
        ParseBlockData(newChunk->flags, src, srcSize);
    }
}


void FreeMapManifest(void){
    free(mapManifest);
}