#pragma once

#include <stddef.h>
#include <stdint.h>

#include "shaders/shaders.h"
#include "shaders/ssbo.h"
#include "modeling/mesh.h"
#include "frame/writer.h"


typedef struct Renderer_t{
    ShaderEffect_t shader;
    RingBuffer_t   ringBuffer;
    MeshRegistry_t meshReg;
    FrameModels_t  modelData;
    size_t         activeOffset;
    size_t         activeSize;
    uint32_t       activeSlice;
    uint8_t        hasActiveSlice;
}Renderer_t;


void InitRenderer(Renderer_t* renderer);

void Render(Renderer_t* renderer);

void DestroyRenderer(Renderer_t* renderer);