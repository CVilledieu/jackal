#include "mesh.h"
#include "error/error.h"

#include "glad/glad.h"
#include <string.h>

void InitMeshRegistry(MeshRegistry_t* reg){
    memset(reg, 0, sizeof(MeshRegistry_t));
}

MeshId RegisterMesh(MeshRegistry_t* reg, const Vertex_t* vertices, uint32_t vertexCount, const uint32_t* indices,  uint32_t indexCount){
    if (reg->count >= MAX_MESHES){
        SoftError("MeshRegistry: capacity reached");
        return MESH_INVALID;
    }

    MeshId id = reg->count;
    Mesh_t* m = &reg->meshes[id];

    glGenVertexArrays(1, &m->vao);
    glGenBuffers(1, &m->vbo);
    glGenBuffers(1, &m->ebo);

    glBindVertexArray(m->vao);

    glBindBuffer(GL_ARRAY_BUFFER, m->vbo);
    glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(Vertex_t), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m->ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(uint32_t), indices, GL_STATIC_DRAW);


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex_t), (void*)offsetof(Vertex_t, position));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex_t), (void*)offsetof(Vertex_t, normal));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex_t), (void*)offsetof(Vertex_t, color));
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex_t), (void*)offsetof(Vertex_t, texCoord));
    glEnableVertexAttribArray(3);

    glBindVertexArray(0);

    m->vertexCount = vertexCount;
    m->indexCount  = indexCount;
    m->active      = 1;

    reg->count++;
    return id;
}



void DestroyMeshRegistry(MeshRegistry_t* reg){
    for (MeshId i = 0; i < reg->count; i++){
        Mesh_t* m = &reg->meshes[i];
        if (m->active){
            glDeleteVertexArrays(1, &m->vao);
            glDeleteBuffers(1, &m->vbo);
            glDeleteBuffers(1, &m->ebo);
            m->active = 0;
        }
    }
    reg->count = 0;
}
