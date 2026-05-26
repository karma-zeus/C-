#ifndef FPS_GAME_H
#define FPS_GAME_H

#include <memory>
#include "window.h"
#include "input.h"
#include "camera.h"
#include "../graphics/renderer.h"
#include "../entity/player.h"
#include "../entity/enemy.h"
#include "../world/world.h"
#include "../physics/physics.h"

namespace FPS
{
    class Game
    {
    public:
        Game(int width, int height, const std::string& title);
        ~Game();

        void run();
        void update(float deltaTime);
        void render();
        void handleInput(float deltaTime);

    private:
        std::unique_ptr<Window> window;
        std::unique_ptr<Input> input;
        std::unique_ptr<Camera> camera;
        std::unique_ptr<Renderer> renderer;
        std::unique_ptr<Player> player;
        std::unique_ptr<World> world;
        std::unique_ptr<Physics> physics;

        std::vector<std::unique_ptr<Enemy>> enemies;
        std::vector<std::unique_ptr<Projectile>> projectiles;

        bool running;
        float gameTime;
    };
}

#endif
