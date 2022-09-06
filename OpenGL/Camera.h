#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

class Camera
{
public:
    Camera(glm::vec3 cameraPosition = glm::vec3(0, 0, 10), glm::vec3 targetPosition = glm::vec3(0, 0, 0), glm::vec3 worldUpDirection = glm::vec3(0, 1, 0));
    Camera(glm::vec3 cameraPosition = glm::vec3(0, 0, 10), float pitch = glm::radians(0.0f), float yaw = glm::radians(0.0f), glm::vec3 worldUpDirection = glm::vec3(0, 1, 0));
    glm::vec3 m_CameraPosition;
    glm::vec3 m_TargetPosition;
    glm::vec3 m_WorldUpDirection;
    float m_Pitch;
    float m_Yaw;
    glm::vec3 m_XDirection;
    glm::vec3 m_YDirection;
    glm::vec3 m_ZDirection;
    float m_Sensitivity;
    glm::mat4 m_ViewMatrix;
public:
    void UpdateCameraZPosition(float zDelta);
    void ProcessMouseMovement(float xDelta, float yDelta);
    glm::mat4 GetViewMatrix();
    void Reset();

    void Debug();
};

std::ostream& operator <<(std::ostream& stream, const glm::vec3& vector3);
