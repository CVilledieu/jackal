#ifndef __MESH_H__
#define __MESH_H__

#include "types.h"

#include <stdint.h>

// ---------------------------------------------------------------------------
// Mesh Registry – central owner of all GPU geometry (VAO/VBO/EBO)
// All systems reference meshes by MeshId; the registry owns the GPU resources.
// ---------------------------------------------------------------------------

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

// Initialise the registry (zeroes all slots)
void     InitMeshRegistry(MeshRegistry_t* reg);

// Upload geometry to the GPU and return a stable MeshId
MeshId   RegisterMesh(MeshRegistry_t* reg,
                      const Vertex_t* vertices, uint32_t vertexCount,
                      const uint32_t* indices,  uint32_t indexCount);

// Bind a mesh's VAO for drawing
void     BindMesh(const MeshRegistry_t* reg, MeshId id);

// Free all GPU resources owned by the registry
void     DestroyMeshRegistry(MeshRegistry_t* reg);

#endif