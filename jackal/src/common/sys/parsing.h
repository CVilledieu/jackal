#pragma once

#include <stdint.h>
#include <string.h>
#include <stdlib.h>

/* Header schema
    - Signature uint32_t
    - Version   uint32_t
    - nKeys     uint32_t
*/


#define MANIFEST_DIR_PATH "assets\\manifests\\"
#define HEADER_SIGNATURE  'JPUP'
#define HEADER_VERSION    1
#define HEADER_SIZE 12


typedef struct ManifestField_t {
    void* fieldPtr;
    size_t length;
} ManifestField_t;


static inline uint64_t Parse_uLE(const uint8_t* src, size_t size){
    uint64_t out = 0;
    for (size_t i = 0; i < size; i++){
        out |= ((uint64_t)src[i]) << (8u * i);
    }
    return out;
}

static inline uint8_t ReadLEField(void* dest, size_t size, uint8_t** src, size_t* srcSize){
    if (*srcSize < size || size == 0 || size > 8){
        return 1;
    }

    uint64_t value = Parse_uLE(*src, size);
    switch (size){
        case 1:
            *(uint8_t*)dest = (uint8_t)value;
            break;
        case 2:
            *(uint16_t*)dest = (uint16_t)value;
            break;
        case 4:
            *(uint32_t*)dest = (uint32_t)value;
            break;
        case 8:
            *(uint64_t*)dest = (uint64_t)value;
            break;
        default:
            return 1;
    }

    *src += size;
    *srcSize -= size;
    return 0;
}

static inline uint8_t ReadBytes(void* dest, size_t destSize, uint8_t** src, size_t* srcSize){
    if (*srcSize < destSize){
        return 1;
    }

    memcpy(dest, *src, destSize);
    *src += destSize;
    *srcSize -= destSize;
    return 0;
}

static inline uint32_t ParseHeader(uint8_t** src, size_t* size){
    if(*size < HEADER_SIZE){
        return 0;
    }
    
    uint32_t signature, version, nKeys;
    if (ReadLEField(&signature, sizeof(signature), src, size)){
        return 0;
    }
    if (ReadLEField(&version, sizeof(version), src, size)){
        return 0;
    }
    if (ReadLEField(&nKeys, sizeof(nKeys), src, size)){
        return 0;
    }
    
    if(signature != (uint32_t)HEADER_SIGNATURE || version != (uint32_t)HEADER_VERSION){
        return 0;
    }

    return nKeys;
}
