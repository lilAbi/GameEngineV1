
#ifndef BLOCKRPG_RENDERSYSTEM_H
#define BLOCKRPG_RENDERSYSTEM_H
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "ECS/System/system.h"
#include "RenderEngine/Core/camera.h"
#include "RenderEngine/Core/shader.h"
#include "GameEngine/Component/componentList.h"
#include "GameEngine/Core/Window/window.h"
#include "ECS/API.h"
#include "Utility/logger.h"

void FrameBufferSizeCallback(GLFWwindow* window, int width, int height);

//should be the last system ran or ran after if nothing else needs updating
class RenderSystem : public ECS::ISystem{
public:
    explicit RenderSystem(GLFWwindow* win) : window{win} {}
    ~RenderSystem() override;
    friend void FrameBufferSizeCallback(GLFWwindow* window, int width, int height);

    //system functions
    void PreUpdate(float deltaTime) override;
    void Update(float deltaTime) override;
    void PostUpdate(float deltaTime) override;
    void Init() override;

    //poll input from keyboard
    void ProcessInput(float deltaTime);

private:
    Shader shader{"src/RenderEngine/Core/shaderFiles/vertShader.vs.glsl", "src/RenderEngine/Core/shaderFiles/fragShader.fs.glsl"};
    Camera camera{};
    GLFWwindow* window = nullptr;
    ECS::EcsEngine* ecsEngine{ECS::Initialize()};

};


#endif //BLOCKRPG_RENDERSYSTEM_H
