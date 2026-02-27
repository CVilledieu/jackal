#include "render.h"
#include "realm.h"
#include "mesh/shaders.h"
#include "mesh/mesh.h"


Renderer_t renderer = {0};

Renderer_t* CreateRenderer(void){
    
    renderer.shaderID =  CreateShader();
    renderer.ssboID = CreateSSBO();
    renderer.meshs = CreateMeshList();
    
    
    return &renderer;
}


void RenderMap(Map_t* currentMap){

}

void RenderEntities(Entities_t* entities){

}

void Render(Manager_t* manager){



}