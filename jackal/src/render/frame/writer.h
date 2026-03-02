#pragma once

#include <stdint.h>
#include <stddef.h>


#define MAX_MESH_COUNT 3

typedef struct FrameModelData_t{
    int meshID;
    int materialID;
    float* model;
} FrameModelData_t;

typedef struct FrameMeshData_t{
    int meshId;
    int nModels;
} FrameMeshData_t;

typedef struct FrameModels_t{
    int dirty;
    int totalModels;
    uint32_t dirtyStart;
    uint32_t dirtyCount;
    FrameModelData_t* modelData;
}FrameModels_t;

typedef struct FrameMeshes_t{
    int dirty; /*Flag for if there were changes to meshes*/
    int totalMeshes;
    FrameMeshData_t meshes[MAX_MESH_COUNT];
} FrameMeshes_t;


typedef struct FrameData_t{
    FrameMeshes_t meshData;
    FrameModels_t modelData;
} FrameData_t;


typedef struct FrameWriter_t {
    size_t writeSize;
    size_t offset;
    uint32_t sliceID;
    void* write;
} FrameWriter_t;

static inline int ValidWriter(FrameWriter_t* writer){
    if (!writer || writer->writeSize == 0){
        return 0;
	}
    return 1;
}