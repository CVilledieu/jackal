#pragma once



typedef struct Renderer_t{
    ShaderEffect_t shader;
    MeshRegistry_t meshReg;
}Renderer_t;


void InitRenderer(Renderer_t* renderer);

void Render(Renderer_t* renderer);

void DestroyRenderer(Renderer_t* renderer);