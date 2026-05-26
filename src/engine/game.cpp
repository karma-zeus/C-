#include "game.h"
#include <glfw3.h>
#include <glm/glm.hpp>
#include <iostream>

namespace FPS
{
    Game::Game(int width, int height, const std::string& title)
        : running(true), gameTime(0.0f)
    {
        window = std::make_unique<Window>(width, height, title);
        input = std::make_unique<Input>();
        camera = std::make_unique<Camera>(glm::vec3(0.0f, 1.8f, 5.0f));
        renderer = std::make_unique<Renderer>(width, height);
        physics = std::make_unique<Physics>();

        // Initialize player
        player = std::make_unique<Player>(glm::vec3(0.0f, 1.8f, 0.0f));

        // Initialize world
        world = std::make_unique<World>();
        world->generateLevel();

        // Spawn some enemies
        for (int i = 0; i < 3; i++)
        {
            enemies.push_back(std::make_unique<Enemy>(
                glm::vec3(i * 5.0f - 5.0f, 1.0f, -10.0f),
                player.get()
            ));
        }

        std::cout << "Game initialized successfully!" << std::endl;
    }

    Game::~Game() = default;

    void Game::run()
    {
        double lastTime = glfwGetTime();

        while (running && !window->shouldClose())
        {
            double currentTime = glfwGetTime();
            float deltaTime = static_cast<float>(currentTime - lastTime);
            lastTime = currentTime;

            handleInput(deltaTime);
            update(deltaTime);
            render();

            window->swapBuffers();
            glfwPollEvents();
        }
    }

    void Game::handleInput(float deltaTime)
    {
        input->update();

        // Player movement
        glm::vec3 movement(0.0f);
        float moveSpeed = 10.0f;

        if (input->isKeyPressed(GLFW_KEY_W))
            movement += camera->getFront() * moveSpeed * deltaTime;
        if (input->isKeyPressed(GLFW_KEY_S))
            movement -= camera->getFront() * moveSpeed * deltaTime;
        if (input->isKeyPressed(GLFW_KEY_A))
            movement -= camera->getRight() * moveSpeed * deltaTime;
        if (input->isKeyPressed(GLFW_KEY_D))
            movement += camera->getRight() * moveSpeed * deltaTime;

        player->move(movement);
        camera->setPosition(player->getPosition() + glm::vec3(0.0f, 0.0f, 0.0f));

        // Mouse look
        double mouseX, mouseY;
        input->getMousePosition(mouseX, mouseY);
        camera->updateRotation(static_cast<float>(mouseX), static_cast<float>(mouseY));
        player->setRotation(camera->getYaw(), camera->getPitch());

        // Shooting
        if (input->isMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
        {
            glm::vec3 projectilePos = player->getPosition() + glm::vec3(0.0f, 0.5f, 0.0f);
            glm::vec3 projectileDir = camera->getFront();
            projectiles.push_back(std::make_unique<Projectile>(projectilePos, projectileDir));
        }

        // Exit
        if (input->isKeyPressed(GLFW_KEY_ESCAPE))
            running = false;
    }

    void Game::update(float deltaTime)
    {
        gameTime += deltaTime;

        // Update player
        player->update(deltaTime);

        // Update camera
        camera->update(deltaTime);

        // Update physics
        physics->update(deltaTime);

        // Update enemies
        for (auto& enemy : enemies)
        {
            enemy->update(deltaTime);
            enemy->chase();
        }

        // Update projectiles
        for (auto it = projectiles.begin(); it != projectiles.end();)
        {
            (*it)->update(deltaTime);

            // Check collision with enemies
            bool hit = false;
            for (auto& enemy : enemies)
            {
                if ((*it)->checkCollision(enemy->getPosition(), 0.5f))
                {
                    enemy->takeDamage(25.0f);
                    hit = true;
                    break;
                }
            }

            // Remove projectile if it hit or is out of range
            if (hit || (*it)->isOutOfRange())
                it = projectiles.erase(it);
            else
                ++it;
        }

        // Remove dead enemies
        enemies.erase(std::remove_if(enemies.begin(), enemies.end(),
            [](const std::unique_ptr<Enemy>& enemy) { return enemy->isDead(); }),
            enemies.end());
    }

    void Game::render()
    {
        renderer->clear();

        // Set up view and projection matrices
        glm::mat4 view = camera->getViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(45.0f),
            1920.0f / 1080.0f, 0.1f, 100.0f);

        renderer->setViewMatrix(view);
        renderer->setProjectionMatrix(projection);

        // Render world
        world->render(renderer.get());

        // Render player
        player->render(renderer.get());

        // Render enemies
        for (auto& enemy : enemies)
            enemy->render(renderer.get());

        // Render projectiles
        for (auto& projectile : projectiles)
            projectile->render(renderer.get());

        // Render HUD
        renderer->renderHUD(player.get(), enemies.size());

        renderer->present();
    }
}
