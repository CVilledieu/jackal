#pragma once

typedef struct MeshList_t MeshList_t; 
typedef struct ModelBuffer_t ModelBuffer_t;

typedef struct Renderer_t{
    unsigned int shaderID;
    unsigned int ssboID;
    MeshList_t* meshs;
    ModelBuffer_t* mapBuffers;
    ModelBuffer_t* entityBuffers;
}Renderer_t;


Renderer_t* CreateRenderer();

void Render(Realm_t* realm);

