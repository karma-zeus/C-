#include "enemy.h"
#include "player.h"
#include <glm/glm.hpp>
#include <glm/geometric.hpp>
#include <iostream>

namespace FPS
{
    Enemy::Enemy(const glm::vec3& startPos, Player* targetPlayer)
        : position(startPos), targetPlayer(targetPlayer), health(50.0f),
          moveSpeed(3.0f), attackCooldown(2.0f), lastAttackTime(0.0f)
    {
    }

    void Enemy::update(float deltaTime)
    {
        lastAttackTime += deltaTime;
    }

    void Enemy::render(Renderer* renderer) const
    {
        // Render enemy model (cube or sphere)
        if (!renderer) return;
        glm::mat4 model = glm::translate(glm::mat4(1.0f), position);
        renderer->renderMesh(model);
    }

    void Enemy::chase()
    {
        if (!targetPlayer) return;

        glm::vec3 toPlayer = targetPlayer->getPosition() - position;
        float distance = glm::length(toPlayer);

        if (distance > 0.1f)
        {
            glm::vec3 direction = glm::normalize(toPlayer);
            position += direction * moveSpeed * 0.016f; // Assuming ~60fps
        }

        // Attack if close enough
        if (distance < 3.0f && lastAttackTime > attackCooldown)
        {
            attack(targetPlayer);
            lastAttackTime = 0.0f;
        }
    }

    void Enemy::takeDamage(float damage)
    {
        health -= damage;
        std::cout << "Enemy hit! Health: " << health << std::endl;
    }

    void Enemy::attack(Player* player)
    {
        if (!player) return;
        player->takeDamage(10.0f);
        std::cout << "Enemy attacks!" << std::endl;
    }
}
