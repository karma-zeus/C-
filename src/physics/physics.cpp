#include "physics.h"

namespace FPS
{
    Physics::Physics() = default;

    void Physics::update(float deltaTime)
    {
        for (auto body : bodies)
        {
            if (!body) continue;

            // Apply gravity
            if (body->useGravity)
            {
                body->acceleration.y = -GRAVITY;
            }

            // Update velocity
            body->velocity += body->acceleration * deltaTime;

            // Update position
            body->position += body->velocity * deltaTime;

            // Ground collision
            if (body->position.y < 0.0f)
            {
                body->position.y = 0.0f;
                body->velocity.y = 0.0f;
            }
        }
    }

    void Physics::addRigidBody(RigidBody* body)
    {
        bodies.push_back(body);
    }

    void Physics::removeRigidBody(RigidBody* body)
    {
        bodies.erase(std::remove(bodies.begin(), bodies.end(), body), bodies.end());
    }
}
