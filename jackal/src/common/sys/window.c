#include "window.h"
#include "error.h"
#include "floader.h"


void WindowResized(GLFWwindow* window, int width, int height){
    (void)window;
    glViewport(0, 0, width, height);
}

GLFWwindow* CreateWindow(char* title){
    if(!glfwInit()){
        CritErr("Failed glfwInit during window creation", "None");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    GLFWwindow* mainWindow = glfwCreateWindow(800, 600, title, NULL, NULL);
    if(!mainWindow){
        glfwTerminate();
        CritErr("mainWindow pointer null after glfwCreateWindow", "None");
    }

    glfwMakeContextCurrent(mainWindow);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        glfwDestroyWindow(mainWindow);
        glfwTerminate();
        CritErr("Error: gladLoader failed", "None");
    }

    glfwSetFramebufferSizeCallback(mainWindow, WindowResized);

    glEnable(GL_DEPTH_TEST);

    GetPathData();

    return mainWindow;
}
