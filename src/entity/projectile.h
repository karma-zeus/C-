#ifndef FPS_PROJECTILE_H
#define FPS_PROJECTILE_H

#include <glm/glm.hpp>
#include "../graphics/renderer.h"

namespace FPS
{
    class Projectile
    {
    public:
        Projectile(const glm::vec3& startPos, const glm::vec3& direction);
        ~Projectile() = default;

        void update(float deltaTime);
        void render(Renderer* renderer) const;
        bool checkCollision(const glm::vec3& targetPos, float radius) const;
        bool isOutOfRange() const;

        glm::vec3 getPosition() const { return position; }

    private:
        glm::vec3 position;
        glm::vec3 direction;
        float speed;
        float lifetime;
        float maxRange;
    };
}

#endif
