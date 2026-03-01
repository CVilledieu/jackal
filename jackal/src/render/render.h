#pragma once

#include "ring_buffer/models.h"

typedef struct DrawData_t{
    unsigned int VAO;
    unsigned int drawLength;
} DrawData_t;

typedef struct Renderer_t{
    unsigned int shaderID;
    RingBuffer_t ringBuffer;
    
}Renderer_t;


void InitRenderer(Renderer_t* renderer);

void Render(Renderer_t* renderer);

void DestroyRenderer(Renderer_t* renderer);