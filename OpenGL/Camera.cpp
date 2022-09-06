#include "Camera.h"

Camera::Camera(glm::vec3 cameraPosition, glm::vec3 targetPosition, glm::vec3 worldUpDirection) : \
m_CameraPosition(cameraPosition), m_TargetPosition(targetPosition), \
m_WorldUpDirection(glm::normalize(worldUpDirection)), m_Sensitivity(0.01f), m_ViewMatrix(glm::mat4(1.0f)), \
m_Pitch(0), m_Yaw(0)
{
    m_ZDirection = glm::normalize(m_TargetPosition - m_CameraPosition);
    m_XDirection = glm::normalize(glm::cross(m_ZDirection, m_WorldUpDirection));
    m_YDirection = glm::normalize(glm::cross(m_XDirection, m_ZDirection));
}

Camera::Camera(glm::vec3 cameraPosition, float pitch, float yaw, glm::vec3 worldUpDirection) :\
m_CameraPosition(cameraPosition), m_Pitch(pitch), m_Yaw(yaw), \
m_WorldUpDirection(glm::normalize(worldUpDirection)), m_Sensitivity(0.01f), m_ViewMatrix(glm::mat4(1.0f))
{
    m_TargetPosition.x = cos(pitch) * sin(yaw);
    m_TargetPosition.y = sin(pitch);
    m_TargetPosition.z = cos(pitch) * cos(yaw);
    m_ZDirection = glm::normalize(m_TargetPosition - m_CameraPosition);
    m_XDirection = glm::normalize(glm::cross(m_ZDirection, m_WorldUpDirection));
    m_YDirection = glm::normalize(glm::cross(m_XDirection, m_ZDirection));
}

void Camera::ProcessMouseMovement(float xDelta, float yDelta)
{
    m_TargetPosition.x += xDelta * m_Sensitivity;
    m_TargetPosition.y += yDelta * m_Sensitivity;
}

glm::mat4 Camera::GetViewMatrix()
{
    m_ViewMatrix = glm::lookAt(m_CameraPosition, m_TargetPosition, m_WorldUpDirection);
    return m_ViewMatrix;
}

void Camera::Reset()
{
    m_CameraPosition = glm::vec3(0, 0, -1);
    m_TargetPosition = glm::vec3(0, 0, 0);
    m_WorldUpDirection = glm::normalize(glm::vec3(0, 1, 0));
}

void Camera::UpdateCameraZPosition(float zDelta)
{
    m_CameraPosition.z += zDelta * m_Sensitivity;
}

std::ostream& operator <<(std::ostream& stream, const glm::vec3& vector3)
{
    stream << "(" << vector3.x << ", " << vector3.y << ", " << vector3.z << ")";
    return stream;
}

void Camera::Debug()
{
    std::cout << "m_CameraPosition:" << m_CameraPosition << std::endl;
    std::cout << "m_TargetPosition:" << m_TargetPosition << std::endl;
    std::cout << "m_WorldUpDirection:" << m_WorldUpDirection << std::endl;
    std::cout << "m_XDirection:" << m_XDirection << std::endl;
    std::cout << "m_YDirection:" << m_YDirection << std::endl;
    std::cout << "m_ZDirection:" << m_ZDirection << std::endl;
    std::cout << "m_Pitch:" << m_Pitch << std::endl;
    std::cout << "m_Yaw:" << m_Yaw << std::endl;
}
