#include "shaders.h"
#include "error/error.h"
#include "floader.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "glad/glad.h"

#define SHADER_DIR "assets\\shaders\\"

void CheckCompiled(unsigned int shader){
    int success = 0;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        CritErr("Failed to compile shader", infoLog);
    }
}

static unsigned int CompileShader(const char* fName, GLenum sType){
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

// Will refactor on a needed basis when different file paths are needed
unsigned int CreateShader(void){
    unsigned int vShade = CompileShader("default.vert", GL_VERTEX_SHADER);
    unsigned int fShade = CompileShader("default.frag", GL_FRAGMENT_SHADER);

    unsigned int shaderID = glCreateProgram();
    glAttachShader(shaderID, vShade);
    glAttachShader(shaderID, fShade);
    glLinkProgram(shaderID);

    glDeleteShader(vShade);
    glDeleteShader(fShade);
    
    return shaderID;
}

unsigned int CreateSSBO(int bufferSize){
    unsigned int ssbo;
    glGenBuffers(1, &ssbo);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
    glBufferData(GL_SHADER_STORAGE_BUFFER, bufferSize, NULL, GL_DYNAMIC_DRAW);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, ssbo);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
    return ssbo;
}