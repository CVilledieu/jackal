#include "jackal.h"
#include "window.h"




JPupEngine_t jpEng = {0};

void InitComponentSystem(void);

JPupEngine_t* JackalPup(char* title){
    jpEng.mainWindow = CreateWindow(title);

}


// Scout should be lead the update, so changes can flow into director before rendering
void Run(void){
    while(!glfwWindowShouldClose(jpEng.mainWindow)){
        ClearBuffer();
        glfwPollEvents();
        
        


        DrawBuffer();
        glfwSwapBuffers(jpEng.mainWindow);
    }
}


