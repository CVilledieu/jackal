#pragma once

typedef struct MeshList_t MeshList_t; 

typedef struct Renderer_t{
    unsigned int shaderID;
    unsigned int ssboID;
    MeshList_t* meshs;

}Renderer_t;

void Render(Manager_t* manager);

