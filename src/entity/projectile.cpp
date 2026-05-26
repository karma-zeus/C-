#include "projectile.h"
#include <glm/geometric.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace FPS
{
    Projectile::Projectile(const glm::vec3& startPos, const glm::vec3& dir)
        : position(startPos), direction(glm::normalize(dir)), speed(50.0f),
          lifetime(0.0f), maxRange(100.0f)
    {
    }

    void Projectile::update(float deltaTime)
    {
        position += direction * speed * deltaTime;
        lifetime += deltaTime;
    }

    void Projectile::render(Renderer* renderer) const
    {
        if (!renderer) return;
        glm::mat4 model = glm::translate(glm::mat4(1.0f), position);
        model = glm::scale(model, glm::vec3(0.1f));
        renderer->renderMesh(model);
    }

    bool Projectile::checkCollision(const glm::vec3& targetPos, float radius) const
    {
        float distance = glm::distance(position, targetPos);
        return distance < radius;
    }

    bool Projectile::isOutOfRange() const
    {
        return lifetime > 5.0f; // 5 second lifetime
    }
}
