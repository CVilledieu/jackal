#pragma once



typedef struct Renderer_t{
    unsigned int shaderID;
    unsigned int ssboID;
    MeshRegistry_t meshs;

}Renderer_t;

void Render(void);

