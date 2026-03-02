#pragma once

#include <stddef.h>
#include <stdint.h>

#include "glad/glad.h"

typedef struct FrameWriter_t FrameWriter_t;

#define BUFFER_COUNT 3

typedef struct BufferSlice_t {
    size_t offset;
    size_t size;
    GLsync fence;
} BufferSlice_t;

typedef struct RingBuffer_t {
    GLuint ssbo;
    uint8_t* mapped;
    size_t sliceSize;
    uint32_t currentSlice;
    BufferSlice_t slices[BUFFER_COUNT];
} RingBuffer_t;

int InitRingBuffer(RingBuffer_t* ring, size_t slotSize);


int GetBufferSlice(RingBuffer_t* ring, FrameWriter_t* writer);
    
void SendBufferSlice(RingBuffer_t* ring, uint32_t slotIndex);

void DestroyRingBuffer(RingBuffer_t* ring);
