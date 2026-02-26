#include "jackal.h"
#include "window.h"
#include "manager.h"
#include "render.h"




Jackal_t* InitJackalEngine(char* title){
    Jackal_t* jEngine = malloc(sizeof(Jackal_t));
    jEngine->mainWindow = CreateWindow(title);

    jEngine->manager = InitManagement();

    return jEngine;
}

void SetOriginIDs(Jackal_t* jEngine, uint32_t mapId){
    jEngine->manager->originMap = mapId;
}

static inline void Prep(Jackal_t* jEngine){
    LoadOrigins(jEngine->manager);
}


void ShutDown(Jackal_t* jEngine){
    DestroyManagement(jEngine->manager);
    DestroyRenderer(jEngine->renderer);
    glfwDestroyWindow(jEngine->mainWindow);
}



void Run(Jackal_t* jEngine){
    Prep(jEngine);
    while(!glfwWindowShouldClose(jEngine->mainWindow)){
        ClearBuffer();
        glfwPollEvents();
        
        


        Render(jEngine->manager);
        glfwSwapBuffers(jEngine->mainWindow);
    }

    ShutDown(jEngine);
}