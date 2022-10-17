
#include "renderSystem.h"

void FrameBufferSizeCallback(GLFWwindow* window, int width, int height){
    Window::winHeight = height;
    Window::winWidth = width;
    glViewport(0, 0, width, height);
};

RenderSystem::~RenderSystem() {
    window = nullptr;
}

void RenderSystem::PreUpdate(float deltaTime){
    util::Logger::Log("Render PreUpdate");
    //process input related to the render system; For now controls the shut down
    ProcessInput(deltaTime);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderSystem::Update(float deltaTime){
    util::Logger::Log("Render Update");
    auto *meshInstanceData = ecsEngine->GetCompOfEntity<MeshInstance>(2);

    std::cout << meshInstanceData->mesh->vertexData.size() << std::endl;

    shader.use();

    glm::mat4 projection = glm::perspective(glm::radians(camera.zoom), (float)Window::winWidth / (float)Window::winHeight, 0.1f, 100.0f);
    shader.setMat4("projection", projection);

    glm::mat4 view = camera.GetViewMatrix();
    shader.setMat4("view", view);

    shader.setMat4("model", glm::mat4(1.0f));


    glBindVertexArray(meshInstanceData->mesh->VAO);

    glDrawArrays(GL_TRIANGLES, 0, meshInstanceData->mesh->vertexData.size());
}

void RenderSystem::PostUpdate(float deltaTime){
    util::Logger::Log("Render PostUpdate");
    glfwSwapBuffers(window);
}

void RenderSystem::Init() {
    glfwSetWindowSizeCallback(window, FrameBufferSizeCallback);
}

void RenderSystem::ProcessInput(float deltaTime) {
    //process mouse
    double xPos, yPos;
    glfwGetCursorPos(window, &xPos, &yPos);
    camera.ProcessMouseMovement((float) xPos, (float) yPos);

    {//process keyboard
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
            camera.ProcessCameraMovement(CFORWARD, deltaTime);
        }
        if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
            camera.ProcessCameraMovement(CBACKWARD, deltaTime);
        }
        if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
            camera.ProcessCameraMovement(CLEFT, deltaTime);
        }
        if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
            camera.ProcessCameraMovement(CRIGHT, deltaTime);
        }
    }
}
