#include "window.h"
#include <glfw3.h>
#include <stdexcept>
#include <iostream>

namespace FPS
{
    Window::Window(int width, int height, const std::string& title)
        : width(width), height(height)
    {
        if (!glfwInit())
            throw std::runtime_error("Failed to initialize GLFW");

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        handle = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
        if (!handle)
            throw std::runtime_error("Failed to create GLFW window");

        glfwMakeContextCurrent(handle);
        glfwSwapInterval(1); // Enable vsync

        // Capture mouse
        glfwSetInputMode(handle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        std::cout << "Window created: " << width << "x" << height << std::endl;
    }

    Window::~Window()
    {
        if (handle)
        {
            glfwDestroyWindow(handle);
        }
        glfwTerminate();
    }

    bool Window::shouldClose() const
    {
        return glfwWindowShouldClose(handle);
    }

    void Window::swapBuffers()
    {
        glfwSwapBuffers(handle);
    }
}
