#pragma once

typedef struct GLFWwindow GLFWwindow;
typedef struct Manager_t Manager_t;
typedef struct Renderer_t Renderer_t;

typedef struct Jackal_t{
    GLFWwindow* mainWindow;
    Manager_t* manager;
    Renderer_t* renderer;
} Jackal_t;


Jackal_t* InitJackalEngine(char* title);

