
#ifndef BLOCKRPG_CAMERA_H
#define BLOCKRPG_CAMERA_H
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

enum CameraDirection{
    CFORWARD,
    CBACKWARD,
    CLEFT,
    CRIGHT
};

class Camera {
public:
    explicit Camera(glm::vec3 pos = {0.0f, 0.0f, 0.0f}) : position{pos} {UpdateCameraProps();}
    //when the mouse moves update camera vectors
    void ProcessMouseMovement(float xPosIn, float yPosIn, bool restrictPitch = true);
    //when key is pressed react to direction
    void ProcessCameraMovement(CameraDirection direction, float deltaTime);
    //return view matrix
    glm::mat4 GetViewMatrix(){return glm::lookAt(position, position+front, up);}
private:
    void UpdateCameraProps();

public:
    //camera properties
    glm::vec3 position;
    glm::vec3 front{0.0f, 0.0f, -1.0f};
    glm::vec3 up{0.0f, 1.0f, 0.0f};
    glm::vec3 right{};
    glm::vec3 worldUp{0.0f, 1.0f, 0.0f};
    float movementSpeed = 2.5f;
    float mouseSensitivty = 2.5f;
    //euler angles
    float yaw{-90.f};
    float pitch{0.0f};
    float lastX{0.0f};
    float lastY{0.0f};
    float zoom{45.0f};
    bool firstMouse{true};

};


#endif //BLOCKRPG_CAMERA_H
