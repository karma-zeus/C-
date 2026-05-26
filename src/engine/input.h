#ifndef FPS_INPUT_H
#define FPS_INPUT_H

#include <glm/glm.hpp>

namespace FPS
{
    class Input
    {
    public:
        Input();
        ~Input() = default;

        void update();
        bool isKeyPressed(int key) const;
        bool isMouseButtonPressed(int button) const;
        void getMousePosition(double& x, double& y) const;

    private:
        double mouseX, mouseY;
        double lastMouseX, lastMouseY;
    };
}

#endif
