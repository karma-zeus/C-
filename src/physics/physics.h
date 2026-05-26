#ifndef FPS_PHYSICS_H
#define FPS_PHYSICS_H

#include <glm/glm.hpp>
#include <vector>

namespace FPS
{
    struct RigidBody
    {
        glm::vec3 position;
        glm::vec3 velocity;
        glm::vec3 acceleration;
        float mass;
        bool useGravity;
    };

    class Physics
    {
    public:
        Physics();
        ~Physics() = default;

        void update(float deltaTime);
        void addRigidBody(RigidBody* body);
        void removeRigidBody(RigidBody* body);

        static constexpr float GRAVITY = 9.8f;

    private:
        std::vector<RigidBody*> bodies;
    };
}

#endif
