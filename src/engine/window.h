#ifndef FPS_WINDOW_H
#define FPS_WINDOW_H

#include <string>
#include <memory>

struct GLFWwindow;

namespace FPS
{
    class Window
    {
    public:
        Window(int width, int height, const std::string& title);
        ~Window();

        bool shouldClose() const;
        void swapBuffers();
        int getWidth() const { return width; }
        int getHeight() const { return height; }
        GLFWwindow* getHandle() const { return handle; }

    private:
        GLFWwindow* handle;
        int width;
        int height;
    };
}

#endif
