#ifndef FPS_ENEMY_H
#define FPS_ENEMY_H

#include <glm/glm.hpp>
#include "../graphics/renderer.h"

namespace FPS
{
    class Player;

    class Enemy
    {
    public:
        Enemy(const glm::vec3& startPos, Player* targetPlayer);
        ~Enemy() = default;

        void update(float deltaTime);
        void render(Renderer* renderer) const;
        void chase();
        void takeDamage(float damage);
        void attack(Player* player);

        glm::vec3 getPosition() const { return position; }
        float getHealth() const { return health; }
        bool isDead() const { return health <= 0.0f; }

    private:
        glm::vec3 position;
        glm::vec3 velocity;
        Player* targetPlayer;
        float health;
        float moveSpeed;
        float attackCooldown;
        float lastAttackTime;
    };
}

#endif
