
#include "camera.h"

void Camera::UpdateCameraProps() {
    //calculate new front vector
    glm::vec3 newFront{cos(glm::radians(yaw)) * cos(glm::radians(pitch)),
                       sin(glm::radians(pitch)),
                       sin(glm::radians(yaw)) * cos(glm::radians(pitch))};
    front = glm::normalize(newFront);
    //recalculate right and up vectors
    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}

void Camera::ProcessMouseMovement(float xPosIn, float yPosIn, bool restrictPitch) {
    if(firstMouse){
        lastX = xPosIn;
        lastY = yPosIn;
        firstMouse = false;
    }

    float xOffset = (xPosIn - lastX) * mouseSensitivty;
    float yOffset = (lastY - yPosIn) * mouseSensitivty;

    lastX = xPosIn;
    lastY = yPosIn;

    yaw += xOffset;
    pitch += yOffset;

    //make sure camera doesnt cause the screen to flip
    if(restrictPitch){
        if (pitch > 89.0f) pitch = 89.0f;
        if (pitch < -89.0f) pitch = -89.0f;
    }

    //update euler angles
    UpdateCameraProps();
}

void Camera::ProcessCameraMovement(CameraDirection direction, float deltaTime) {

    float velocity{movementSpeed*deltaTime};

    if(direction == CFORWARD)
        position += (front * velocity);
    if(direction == CBACKWARD)
        position -= (front * velocity);
    if(direction == CLEFT)
        position -= (right * velocity);
    if(direction == CRIGHT)
        position += (right * velocity);
}
