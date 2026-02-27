#pragma once

typedef struct GLFWwindow GLFWwindow;
typedef struct Realm_t Realm_t;
typedef struct Renderer_t Renderer_t;

typedef struct Jackal_t{
    GLFWwindow* mainWindow;
    Realm_t* realm;
    Renderer_t* renderer;
} Jackal_t;


Jackal_t* InitJackalEngine(char* title);
void Run(Jackal_t* jEngine);



void SetOriginIDs(Jackal_t* jEngine, uint32_t mapId);