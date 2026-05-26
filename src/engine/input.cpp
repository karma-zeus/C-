#include "input.h"
#include <glfw3.h>

namespace FPS
{
    Input::Input() : mouseX(0.0), mouseY(0.0), lastMouseX(0.0), lastMouseY(0.0)
    {
    }

    void Input::update()
    {
        lastMouseX = mouseX;
        lastMouseY = mouseY;
        // Mouse position is updated via GLFW callbacks
    }

    bool Input::isKeyPressed(int key) const
    {
        GLFWwindow* window = glfwGetCurrentContext();
        return glfwGetKey(window, key) == GLFW_PRESS;
    }

    bool Input::isMouseButtonPressed(int button) const
    {
        GLFWwindow* window = glfwGetCurrentContext();
        return glfwGetMouseButton(window, button) == GLFW_PRESS;
    }

    void Input::getMousePosition(double& x, double& y) const
    {
        GLFWwindow* window = glfwGetCurrentContext();
        glfwGetCursorPos(window, &mouseX, &mouseY);
        x = mouseX;
        y = mouseY;
    }
}
