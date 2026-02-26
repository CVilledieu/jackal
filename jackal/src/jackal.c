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


// Scout should be lead the update, so changes can flow into director before rendering
void Run(Jackal_t* jEngine){
    while(!glfwWindowShouldClose(jEngine->mainWindow)){
        ClearBuffer();
        glfwPollEvents();
        
        


        Render(jEngine->manager);
        glfwSwapBuffers(jEngine->mainWindow);
    }

    ShutDown(jEngine);
}


void ShutDown(Jackal_t* jEngine){
    DestroyManagement(jEngine->manager);
    DestroyRenderer(jEngine->renderer);
    glfwDestroyWindow(jEngine->mainWindow);
}