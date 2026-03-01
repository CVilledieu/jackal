#include "jackal.h"
#include "window.h"
#include "realm.h"
#include "render.h"



/* Processes that cant be in init, but need to happen before main loop */
static inline void LastMinute(Jackal_t* jEngine){
    LoadOrigins(jEngine->realm);
}


static inline void ShutDown(Jackal_t* jEngine){
    DestroyManagement(jEngine->realm);
    DestroyRenderer(jEngine->renderer);
    glfwDestroyWindow(jEngine->mainWindow);
}



Jackal_t* CreateEngine(char* title){
    Jackal_t* jEngine = malloc(sizeof(Jackal_t));
    jEngine->mainWindow = CreateWindow(title);

    jEngine->realm = NewRealm();
    InitRenderer(jEngine->renderer);

    return jEngine;
}

/* */
void SetOriginIDs(Jackal_t* jEngine, uint32_t mapId){
    jEngine->realm->originMap = mapId;
}



void Run(Jackal_t* jEngine){

    LastMinute(jEngine);

    while(!glfwWindowShouldClose(jEngine->mainWindow)){
        ClearBuffer();
        glfwPollEvents();
        
        
        Update();

        Render(jEngine->realm);
        glfwSwapBuffers(jEngine->mainWindow);
    }

    ShutDown(jEngine);
}