#include "render.h"
#include "manager.h"
#include "mesh/shaders.h"
#include "mesh/mesh.h"


Renderer_t renderer = {0};

void CreateRenderer(void){
    
    renderer.shaderID =  CreateShader();
    renderer.ssboID = CreateSSBO();
}



void RenderMap(Map_t* currentMap){

}

void RenderEntities(Entities_t* entities){

}

void Render(Manager_t* manager){



}