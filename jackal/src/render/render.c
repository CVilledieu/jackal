#include "render.h"
#include "realm.h"
#include "mesh/shaders.h"
#include "mesh/mesh.h"
#include "writer.h"
#include "component_data/component_data.h"
#include "ring_buffer/models.h"
#include "glad/glad.h"



void InitRenderer(Renderer_t* renderer){
    renderer->shaderID =  CreateShader();
    InitRingBuffer(&renderer->ringBuffer);
    
    glUseProgram(renderer->shaderID); /*Only one shader at the moment // set and forget*/
    return &renderer;
}




static inline void DrawComponent(DrawData_t* drawData){
    /*SetDrawIndexUniform();*/
    glBindVertexArray(drawData->VAO);
    glDrawElements(GL_TRIANGLES, drawData->drawLength, GL_UNSIGNED_INT, 0);
}



void Render(Renderer_t* renderer){
    FrameWriter_t writer = {0, 0, 0, NULL};
    GetBufferSlice(&renderer->ringBuffer, &writer);
    
    glBindBufferRange(GL_SHADER_STORAGE_BUFFER, /*MODEL_BINDING_SLOT*/, renderer->ringBuffer.ssbo, writer.offset, writer.writeSize);
    DrawComponent();
    DrawComponent();

    
    glBindVertexArray(0);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, );

    SendBufferSlice(&renderer->ringBuffer, writer.sliceID);
}



void DestroyRenderer(Renderer_t* renderer){
    DestroyRingBuffer(&renderer->ringBuffer);
}