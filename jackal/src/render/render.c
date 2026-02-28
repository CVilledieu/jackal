#include "render.h"
#include "realm.h"
#include "mesh/shaders.h"
#include "mesh/mesh.h"
#include "writer.h"

Renderer_t renderer = {0};

Renderer_t* CreateRenderer(void){
    renderer.shaderID =  CreateShader();
    InitRingBuffer(&renderer.ringBuffer);
    
    return &renderer;
}


void RenderMap(Map_t* currentMap){
    FrameWriter_t writer = {0, 0, 0, NULL};
    GetBufferSlice(&renderer.ringBuffer, &writer);


    SendBufferSlice(&renderer.ringBuffer, writer.sliceID);
}

void RenderEntities(Entities_t* entities){
    FrameWriter_t writer = {0, 0, 0, NULL};
    GetBufferSlice(&renderer.ringBuffer, &writer);


    SendBufferSlice(&renderer.ringBuffer, writer.sliceID);
}

void Render(Realm_t* realm){
    RenderMap();
    RenderEntities();
}

void DestroyRenderer(Renderer_t* renderer){
    DestroyRingBuffer(renderer->ringBuffer);
}