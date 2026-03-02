#include "shaders.h"
#include "error/error.h"
#include "floader.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "glad/glad.h"

#define SHADER_DIR "assets\\shaders\\"



static inline void CheckCompiled(unsigned int shader){
    int success = 0;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        CritErr("Failed to compile shader", infoLog);
    }
}



static inline unsigned int CompileShader(const char* fName, GLenum sType){
    uint8_t* dataBuffer;
    uint32_t fSize = GetFileData(&dataBuffer, SHADER_DIR, fName);

    unsigned int shader = glCreateShader(sType);
    const char* constBufferPtr = (const char*)dataBuffer;
    glShaderSource(shader, 1, &constBufferPtr, NULL);

    glCompileShader(shader);
    CheckCompiled(shader);

    free(dataBuffer);
    return shader;
}



static inline void GetUniformLocations(ShaderEffect_t* sEffect){
    sEffect->uniforms.view = glGetUniformLocation(sEffect->programID, VIEW_UNIFORM);
    sEffect->uniforms.drawIndex = glGetUniformLocation(sEffect->programID, DRAW_INDEX_UNIFORM);
}



static inline void CreateShaderProgram(ShaderEffect_t* sEffect){
    unsigned int vertexShader = CompileShader("default.vert", GL_VERTEX_SHADER);
    unsigned int fragmentShader = CompileShader("default.frag", GL_FRAGMENT_SHADER);
    
    sEffect->programID = glCreateProgram();
    glAttachShader(sEffect->programID, vertexShader);
    glAttachShader(sEffect->programID, fragmentShader);
    glLinkProgram(sEffect->programID);
    
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}



void InitShaderEffect(ShaderEffect_t* sEffect, size_t sliceSize){  
    sEffect->layoutBinding = 0;
    CreateShaderProgram(sEffect);

    GetUniformLocations(sEffect);
    InitRingBuffer(&sEffect->ringBuffer, sliceSize);
}



int DestroyShaderEffect(ShaderEffect_t* sEffect){
    glUseProgram(0);
    glDeleteProgram(sEffect->programID);
}