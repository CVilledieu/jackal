#include "render.h"
#include "shaders/shaders.h"
#include "shaders/writer.h"
#include "shaders/ssbo.h"
#include "modeling/frame.h"

#include "glad/glad.h"

#define SSBO_BINDING_INDEX 0




static inline void DrawFrame(Frame_t* frame){
    /*SetDrawIndexUniform();*/
    glBindVertexArray(frame->map.VAO);
    glDrawElements(GL_TRIANGLES, frame->map.drawLength, GL_UNSIGNED_INT, 0);

    glBindVertexArray(frame->map.VAO);
    glDrawElements(GL_TRIANGLES, frame->map.drawLength, GL_UNSIGNED_INT, 0);
}



void Render(Renderer_t* renderer){
    FrameWriter_t writer = {0, 0, 0, NULL};
    GetBufferSlice(&renderer->shader.ringBuffer, &writer);

    FrameModels_t* modelData = (FrameModels_t*)writer->write;
    modelData->mapData.models = GetMapModels();
    modelData->mapData.material = GetMapMaterials();
    modelData->entityData.models = GetEntityModels();
    modelData->entityData.material = GetEntityMaterials();


    glBindBufferRange(GL_SHADER_STORAGE_BUFFER, SSBO_BINDING_INDEX, renderer->shader.ringBuffer.ssbo, writer.offset, writer.writeSize);
    
    DrawFrame(&renderer->frameData);
    
    glBindVertexArray(0);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, SSBO_BINDING_INDEX, 0);
    SendBufferSlice(&renderer->shader.ringBuffer, writer.sliceID);
}



void DestroyRenderer(Renderer_t* renderer){
    DestroyRingBuffer(&renderer->shader.ringBuffer);
    DestroyShaderEffect(&renderer->shader);
}



void InitRenderer(Renderer_t* renderer){
    renderer->shaderCount = 0;
    InitShaderEffect(&renderer->shader);
    InitModeling();
    
    SetShaderProgram(&renderer->shader); /*Only one shader at the moment // set and forget*/
    return &renderer;
}