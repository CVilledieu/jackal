#pragma once

#include "ring_buffer/models.h"


typedef struct Renderer_t{
    unsigned int shaderID;
    RingBuffer_t ringBuffer;
}Renderer_t;


Renderer_t* CreateRenderer();

void Render(Realm_t* realm);

void DestroyRenderer(void);