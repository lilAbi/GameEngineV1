#include "window.h"


//destroy the glfw context
Window::~Window() {
    glfwTerminate();
}

//init glfw
void Window::Init() {
    //initialize glfw
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    //create the window, if it fails then just tERMINATE
    window = glfwCreateWindow( winWidth,winHeight, "blockRPG", nullptr, nullptr);
    if (window == nullptr){
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(window);

    //if glad doesnt work then return; NO ERROR CHECKING ASSUME IT WORKS LOL
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        return;
    }

    glEnable(GL_DEPTH_TEST);

}