#ifndef FPS_RENDERER_H
#define FPS_RENDERER_H

#include <glm/glm.hpp>
#include <memory>
#include <string>

namespace FPS
{
    class Player;
    class Shader;

    class Renderer
    {
    public:
        Renderer(int width, int height);
        ~Renderer();

        void clear();
        void present();
        void renderHUD(Player* player, size_t enemyCount);

        void setViewMatrix(const glm::mat4& view);
        void setProjectionMatrix(const glm::mat4& projection);
        glm::mat4 getViewMatrix() const { return viewMatrix; }
        glm::mat4 getProjectionMatrix() const { return projectionMatrix; }

        void renderMesh(const glm::mat4& model) const;

    private:
        int width, height;
        glm::mat4 viewMatrix;
        glm::mat4 projectionMatrix;
        std::unique_ptr<Shader> basicShader;
        std::unique_ptr<Shader> hudShader;

        void initializeShaders();
    };
}

#endif
