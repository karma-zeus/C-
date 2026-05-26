#include "world.h"
#include "../graphics/renderer.h"
#include "../graphics/mesh.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

namespace FPS
{
    World::World() = default;

    void World::generateLevel()
    {
        // Create floor
        auto floorMesh = Mesh::createPlane(100.0f, 100.0f);
        glm::mat4 floorModel = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
        objects.push_back({floorModel, floorMesh});

        // Create some walls and obstacles
        auto cubeMesh = Mesh::createCube();
        for (int i = 0; i < 5; i++)
        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(i * 10.0f - 20.0f, 2.0f, -30.0f));
            model = glm::scale(model, glm::vec3(3.0f, 4.0f, 3.0f));
            objects.push_back({model, cubeMesh});
        }

        std::cout << "Level generated with " << objects.size() << " objects" << std::endl;
    }

    void World::render(Renderer* renderer) const
    {
        if (!renderer) return;

        for (const auto& obj : objects)
        {
            renderer->renderMesh(obj.first);
        }
    }
}
