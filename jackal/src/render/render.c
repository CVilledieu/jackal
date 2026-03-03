#include "render.h"
#include "frame.h"
#include "frame/writer.h"
#include "shaders/shaders.h"
#include "shaders/ssbo.h"
#include "modeling/mesh.h"
#include "glad/glad.h"
#include <string.h>



static inline void WriteFrameData(const FrameBuildResult_t* result, FrameWriter_t* writer){
    if (!result || !writer || !writer->write || !result->payload) {
        return;
    }

    uint8_t* writePtr = (uint8_t*)writer->write;
    const uint8_t* srcPtr = (const uint8_t*)result->payload;

    for (uint32_t i = 0; i < result->dirtySpanCount; i++) {
        const FrameDirtySpan_t* span = &result->dirtySpans[i];
        memcpy(writePtr + span->offset, srcPtr + span->offset, span->size);
    }
}

static inline void DrawActiveMeshes(const FrameBuildResult_t* frame, MeshRegistry_t* registry, ShaderEffect_t* sEffect){
    if (!frame || frame->meshTrackCount == 0) {
        return;
    }

    unsigned int uDrawIndexAddress = sEffect->uniforms.drawIndex;
    for (uint32_t i = 0; i < frame->meshTrackCount; i++) {
        const FrameMeshTrack_t* meshTrack = &frame->meshTracks[i];
        if (meshTrack->meshID < 0 || meshTrack->meshID >= registry->count || meshTrack->modelCount == 0) {
            continue;
        }

        Mesh_t mesh = registry->meshes[meshTrack->meshID];
        if (!mesh.active) {
            continue;
        }

        glUniform1i(uDrawIndexAddress, (int)meshTrack->modelStart);
        glBindVertexArray(mesh.vao);
        glDrawElementsInstanced(GL_TRIANGLES, mesh.indexCount, GL_UNSIGNED_INT, 0, (GLsizei)meshTrack->modelCount);
    }
}



void Render(Renderer_t* renderer){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    FrameBuildResult_t frameResult = {0};
    if (!BuildFrameModels(&frameResult, &renderer->modelData)) {
        return;
    }

    if (!renderer->hasActiveSlice || frameResult.dirtySpanCount > 0) {
        FrameWriter_t writer = {frameResult.requiredSize, 0, 0, NULL};
        if (!GetBufferSlice(&renderer->ringBuffer, &writer)) {
            return;
        }

        WriteFrameData(&frameResult, &writer);

        renderer->activeOffset = writer.offset;
        renderer->activeSize = writer.writeSize;
        renderer->activeSlice = writer.sliceID;
        renderer->hasActiveSlice = 1;

        SendBufferSlice(&renderer->ringBuffer, writer.sliceID);
    }

    if (renderer->activeSize == 0) {
        return;
    }

    glBindBufferRange(GL_SHADER_STORAGE_BUFFER, renderer->shader.layoutBinding, renderer->ringBuffer.ssbo, renderer->activeOffset, renderer->activeSize);
	DrawActiveMeshes(&frameResult, &renderer->meshReg, &renderer->shader);


    glBindVertexArray(0);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, renderer->shader.layoutBinding, 0);
}



void DestroyRenderer(Renderer_t* renderer){
    DestroyRingBuffer(&renderer->ringBuffer);
    DestroyShaderEffect(&renderer->shader);
}



void InitRenderer(Renderer_t* renderer){
    const size_t sliceSize = 1024; /* TEMP VALUE*/
    renderer->activeOffset = 0;
    renderer->activeSize = 0;
    renderer->activeSlice = 0;
    renderer->hasActiveSlice = 0;

    InitShaderEffect(&renderer->shader, sliceSize);
    InitRingBuffer(&renderer->ringBuffer, sliceSize);
    InitModeling();
    
    SetShaderProgram(&renderer->shader); /*Only one shader at the moment // set and forget*/
}