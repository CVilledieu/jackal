#include "render.h"
#include "realm.h"
#include "mesh/shaders.h"
#include "mesh/mesh.h"


Renderer_t renderer = {0};

Renderer_t* CreateRenderer(void){
    renderer.shaderID =  CreateShader();
    InitRingBuffer(&renderer.ringBuffer);
    
    return &renderer;
}


void RenderMap(Map_t* currentMap){

}

void RenderEntities(Entities_t* entities){

}

void Render(Realm_t* realm){
    FrameWriter_t fWriter = {.start = NULL, 0, 0};


}

void DestroyRenderer(void){
    DestroyRingBuffer(&renderer.ringBuffer);
}