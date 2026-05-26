#ifndef FPS_CAMERA_H
#define FPS_CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace FPS
{
    class Camera
    {
    public:
        Camera(const glm::vec3& position);
        ~Camera() = default;

        void update(float deltaTime);
        void updateRotation(float mouseX, float mouseY);
        void setPosition(const glm::vec3& pos) { position = pos; }

        glm::mat4 getViewMatrix() const;
        glm::vec3 getPosition() const { return position; }
        glm::vec3 getFront() const { return front; }
        glm::vec3 getRight() const { return right; }
        glm::vec3 getUp() const { return up; }
        float getYaw() const { return yaw; }
        float getPitch() const { return pitch; }

    private:
        glm::vec3 position;
        glm::vec3 front;
        glm::vec3 right;
        glm::vec3 up;
        glm::vec3 worldUp;

        float yaw;
        float pitch;
        float lastMouseX;
        float lastMouseY;
        bool firstMouse;
        const float mouseSensitivity = 0.1f;
    };
}

#endif
