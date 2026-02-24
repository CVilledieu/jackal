#pragma once

#include "glad/glad.h"
#include <glfw/glfw3.h>

GLFWwindow* CreateWindow(char* title);

static inline void ClearBuffer(void){
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f); 
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

