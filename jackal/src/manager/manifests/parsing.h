#pragma once

#include <stdint.h>
#include <string.h>
#include <stdlib.h>

/*
    Parsing is a support for both mapio and entityio
    both map and entity files contain the same header structure, but differ with the page data
*/
#define MANIFEST_DIR_PATH "assets\\stage\\"
#define FILE_SIGNATURE  0
#define FILE_VERSION    0


/* Header schema
    - Signature uint32_t
    - Version   uint32_t
    - nKeys     uint32_t

    Header was originally a struct, but seemed wasteful as I was checking the signature and version almost right away.
    If more common properties are needed the header struct may return, but at the moment return nKeys from ParseHeader works
*/
#define FILE_HEADER_SIZE 12



static inline void CopyData(void* dest, size_t destSize, uint8_t** src, size_t* srcSize){
    memcpy(dest, *src, destSize);
    *src += destSize;
    *srcSize -= destSize;
}

static inline uint32_t ParseHeader(uint8_t** src, size_t* size){
    if(*size < FILE_HEADER_SIZE){
        return 0;
    }
    
    uint32_t signature, version, nKeys;
    CopyData(&signature, sizeof(signature), src, size);
    CopyData(&version, sizeof(version), src, size);
    CopyData(&nKeys, sizeof(nKeys), src, size);
    
    if(signature != (uint32_t)FILE_SIGNATURE || version != (uint32_t)FILE_VERSION){
        return 0;
    }

    return nKeys;
}
