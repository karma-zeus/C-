#include "camera.h"
#include <glm/gtc/matrix_transform.hpp>

namespace FPS
{
    Camera::Camera(const glm::vec3& position)
        : position(position), worldUp(glm::vec3(0.0f, 1.0f, 0.0f)),
          yaw(-90.0f), pitch(0.0f), lastMouseX(0.0f), lastMouseY(0.0f),
          firstMouse(true)
    {
        front = glm::vec3(0.0f, 0.0f, -1.0f);
        right = glm::normalize(glm::cross(front, worldUp));
        up = glm::normalize(glm::cross(right, front));
    }

    void Camera::update(float deltaTime)
    {
        // Camera update logic
    }

    void Camera::updateRotation(float mouseX, float mouseY)
    {
        if (firstMouse)
        {
            lastMouseX = mouseX;
            lastMouseY = mouseY;
            firstMouse = false;
        }

        float xoffset = mouseX - lastMouseX;
        float yoffset = lastMouseY - mouseY;
        lastMouseX = mouseX;
        lastMouseY = mouseY;

        xoffset *= mouseSensitivity;
        yoffset *= mouseSensitivity;

        yaw += xoffset;
        pitch += yoffset;

        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;

        glm::vec3 direction;
        direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        direction.y = sin(glm::radians(pitch));
        direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        front = glm::normalize(direction);
        right = glm::normalize(glm::cross(front, worldUp));
        up = glm::normalize(glm::cross(right, front));
    }

    glm::mat4 Camera::getViewMatrix() const
    {
        return glm::lookAt(position, position + front, up);
    }
}
