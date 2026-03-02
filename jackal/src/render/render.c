#include "render.h"
#include "shaders/shaders.h"
#include "shaders/writer.h"
#include "shaders/ssbo.h"
#include "modeling/mesh.h"
#include "glad/glad.h"

#define SSBO_BINDING_INDEX 0




static inline void DrawMeshes(Mesh_t* mesh, unsigned int shaderAddress, unsigned int drawIndex){
    glUniform1i(shaderAddress, drawIndex);
    glBindVertexArray(mesh->vao);
    glDrawElements(GL_TRIANGLES, mesh->indexCount, GL_UNSIGNED_INT, 0);
}



static inline void SetFrameModels(FrameWriter_t* writer){
    FrameModels_t* modelData = (FrameModels_t*)writer->write;
}



void Render(Renderer_t* renderer){
    FrameWriter_t writer = {0, 0, 0, NULL};
    GetBufferSlice(&renderer->shader.ringBuffer, &writer);

    FrameModels_t* modelData = (FrameModels_t*)writer.write;


    glBindBufferRange(GL_SHADER_STORAGE_BUFFER, SSBO_BINDING_INDEX, renderer->shader.ringBuffer.ssbo, writer.offset, writer.writeSize);
    const unsigned int uDrawIndex = renderer->shader.uniforms.drawIndex; 
    for (int i = 0; i < (int)renderer->meshes.count; i++){
        Mesh_t* mesh = &renderer->meshReg.meshes[i];
        SetShaderUniform(&renderer->shader, DRAW_INDEX_UNIFORM, i);
        DrawMesh(&renderer->mesh)
    }
    
    glBindVertexArray(0);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, SSBO_BINDING_INDEX, 0);
    SendBufferSlice(&renderer->shader.ringBuffer, writer.sliceID);
}



void DestroyRenderer(Renderer_t* renderer){
    DestroyRingBuffer(&renderer->shader.ringBuffer);
    DestroyShaderEffect(&renderer->shader);
}



void InitRenderer(Renderer_t* renderer){
    renderer->nMeshes  = 0;
    const size_t sliceSize = 1024;
    InitShaderEffect(&renderer->shader, sliceSize);
    InitModeling();
    
    SetShaderProgram(&renderer->shader); /*Only one shader at the moment // set and forget*/
    return &renderer;
}