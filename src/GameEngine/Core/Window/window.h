#ifndef BLOCKRPG_WINDOW_H
#define BLOCKRPG_WINDOW_H
#include "glad/glad.h"
#include "GLFW/glfw3.h"

class Window {
public:
    Window() = default;
    ~Window();
    //init glfw
    void Init();
    //returns glfw window obj
    GLFWwindow* operator()() { return window;}
public:
    inline static int winHeight{600};
    inline static int winWidth{800};
private:
    GLFWwindow*     window{nullptr};
};

#endif //BLOCKRPG_WINDOW_H
