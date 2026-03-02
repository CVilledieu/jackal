#pragma once

#include "ssbo.h"
#define VIEW_UNIFORM "uView"
#define DRAW_INDEX_UNIFORM "uDrawIndex"

typedef struct UniformLocations_t {
    unsigned int view;
    unsigned int drawIndex;
} UniformLocations_t;

typedef struct ShaderEffect_t{
    unsigned int programID;
    unsigned int layoutBinding;
    UniformLocations_t uniforms;
    RingBuffer_t ringBuffer;
}ShaderEffect_t;



void InitShaderEffect(ShaderEffect_t* sEffect, size_t sliceSize);
int DestroyShaderEffect(ShaderEffect_t* sEffect);

static inline void SetShaderProgram(ShaderEffect_t* sEffect){
    glUseProgram(sEffect->programID);
}