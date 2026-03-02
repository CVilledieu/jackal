#pragma once

#include "types.h"

#include <stdint.h>



#define MAX_MESHES 64

typedef struct Mesh_t {
    unsigned int vao;
    unsigned int vbo;
    unsigned int ebo;
    uint32_t     vertexCount;
    uint32_t     indexCount;
    uint8_t      active;
} Mesh_t;

typedef struct MeshRegistry_t {
    Mesh_t  meshes[MAX_MESHES];
    MeshId  count;
} MeshRegistry_t;


void     InitMeshRegistry(MeshRegistry_t* reg);
MeshId   RegisterMesh(MeshRegistry_t* reg, const Vertex_t* vertices, uint32_t vertexCount, const uint32_t* indices,  uint32_t indexCount);
void     DestroyMeshRegistry(MeshRegistry_t* reg);
