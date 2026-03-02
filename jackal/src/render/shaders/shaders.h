#pragma once

#include "ssbo.h"



typedef struct ShaderEffect_t{
    unsigned int shaderType;
    unsigned int programID;
    unsigned int model_index;
    RingBuffer_t ringBuffer;
}ShaderEffect_t;



void InitShaderEffect(ShaderEffect_t* sEffect);
int DestroyShaderEffect(ShaderEffect_t* sEffect);

static inline void SetShaderProgram(ShaderEffect_t* sEffect){
    glUseProgram(sEffect->programID);
}