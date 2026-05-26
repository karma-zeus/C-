#ifndef FPS_WORLD_H
#define FPS_WORLD_H

#include <vector>
#include <memory>
#include <glm/glm.hpp>

namespace FPS
{
    class Renderer;
    class Mesh;

    class World
    {
    public:
        World();
        ~World() = default;

        void generateLevel();
        void render(Renderer* renderer) const;

    private:
        std::vector<std::pair<glm::mat4, std::shared_ptr<Mesh>>> objects;
    };
}

#endif
