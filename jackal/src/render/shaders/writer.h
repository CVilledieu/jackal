#pragma once

#include <stdint.h>


#define MAX_MAP_MODELS 16
#define MAX_ENTITY_MODELS 16

typedef struct MapDrawData_t{
    float models[MAX_MAP_MODELS];
    int material[MAX_MAP_MODELS];
} MapDrawData_t;

typedef struct EntityDrawData_t{
    float models[MAX_ENTITY_MODELS];
    int material[MAX_ENTITY_MODELS];
} EntityDrawData_t;

typedef struct FrameModels_t{
    MapDrawData_t mapData;
    EntityDrawData_t entityData;
}FrameModels_t;



typedef struct FrameWriter_t {
    size_t writeSize;
    size_t offset;
    uint32_t sliceID;
    void* write;
} FrameWriter_t;

static inline int ValidWriter(FrameWriter_t* writer){
	if (!writer->write || !writer->offset || !writer->sliceID || !writer->writeSize){
        return 0;
	}
    return 1;
}