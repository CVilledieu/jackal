#ifndef __JACKAL_PARSING_H__
#define __JACKAL_PARSING_H__

#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#define MAP_FNAME "maps.jpup"

#define FILE_SIGNATURE  0
#define FILE_VERSION    0


typedef struct FileHeader_t{
    uint32_t signature;
    uint32_t version;
    uint32_t nKeys;
} FileHeader_t;
#define FILE_HEADER_SIZE 12



static inline void CopyData(void* dest, size_t destSize, uint8_t** src, size_t* srcSize){
    memcpy(dest, *src, destSize);
    *src += destSize;
    *srcSize -= destSize;
}

static inline FileHeader_t* ParseHeader(uint8_t** src, size_t* size){
    if(*size < FILE_HEADER_SIZE){
        return NULL;
    }
    FileHeader_t* header = calloc(1, sizeof(FileHeader_t));

    CopyData(&header->signature, sizeof(header->signature), src, size);
    CopyData(&header->version, sizeof(header->version), src, size);
    CopyData(&header->nKeys, sizeof(header->nKeys), src, size);
    
    if(header->signature != (uint32_t)FILE_SIGNATURE || header->version != (uint32_t)FILE_VERSION){
        free(header);
        return NULL;
    }

    return header;
}


#endif