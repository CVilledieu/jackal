#pragma once


typedef struct DrawData_t{
    unsigned int VAO;
    unsigned int drawLength;
} DrawData_t;

typedef struct Renderer_t{
    unsigned int shaderCount;
    ShaderEffect_t shader;
    Frame_t frameData;
}Renderer_t;


void InitRenderer(Renderer_t* renderer);

void Render(Renderer_t* renderer);

void DestroyRenderer(Renderer_t* renderer);