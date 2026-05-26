#include "renderer.h"
#include "shader.h"
#include "../entity/player.h"
#include <GL/gl.h>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

namespace FPS
{
    Renderer::Renderer(int width, int height)
        : width(width), height(height),
          viewMatrix(glm::mat4(1.0f)),
          projectionMatrix(glm::mat4(1.0f))
    {
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

        initializeShaders();
        std::cout << "Renderer initialized" << std::endl;
    }

    Renderer::~Renderer() = default;

    void Renderer::initializeShaders()
    {
        // Basic 3D shader
        std::string vertexShader = R"(
            #version 330 core
            layout (location = 0) in vec3 position;
            layout (location = 1) in vec3 normal;
            layout (location = 2) in vec2 texCoord;

            uniform mat4 view;
            uniform mat4 projection;
            uniform mat4 model;

            out vec3 FragPos;
            out vec3 Normal;
            out vec2 TexCoord;

            void main()
            {
                FragPos = vec3(model * vec4(position, 1.0));
                Normal = mat3(transpose(inverse(model))) * normal;
                TexCoord = texCoord;
                gl_Position = projection * view * vec4(FragPos, 1.0);
            }
        )";

        std::string fragmentShader = R"(
            #version 330 core
            in vec3 FragPos;
            in vec3 Normal;
            in vec2 TexCoord;

            uniform vec3 objectColor;
            uniform vec3 lightPos;
            uniform vec3 viewPos;

            out vec4 FragColor;

            void main()
            {
                // Lighting
                vec3 lightColor = vec3(1.0);
                float ambientStrength = 0.3;
                vec3 ambient = ambientStrength * lightColor;

                vec3 norm = normalize(Normal);
                vec3 lightDir = normalize(lightPos - FragPos);
                float diff = max(dot(norm, lightDir), 0.0);
                vec3 diffuse = diff * lightColor;

                vec3 result = (ambient + diffuse) * objectColor;
                FragColor = vec4(result, 1.0);
            }
        )";

        basicShader = std::make_unique<Shader>(vertexShader, fragmentShader);
    }

    void Renderer::clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Renderer::present()
    {
        // Presentation is handled by window.swapBuffers()
    }

    void Renderer::setViewMatrix(const glm::mat4& view)
    {
        viewMatrix = view;
    }

    void Renderer::setProjectionMatrix(const glm::mat4& projection)
    {
        projectionMatrix = projection;
    }

    void Renderer::renderMesh(const glm::mat4& model) const
    {
        if (!basicShader) return;

        basicShader->use();
        basicShader->setMat4("view", viewMatrix);
        basicShader->setMat4("projection", projectionMatrix);
        basicShader->setMat4("model", model);
    }

    void Renderer::renderHUD(Player* player, size_t enemyCount)
    {
        // HUD rendering (2D overlay)
        // This would use orthographic projection and 2D rendering
        glDisable(GL_DEPTH_TEST);

        // Render crosshair and UI elements here

        glEnable(GL_DEPTH_TEST);
    }
}
