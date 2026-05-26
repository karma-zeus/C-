#include "player.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

namespace FPS
{
    Player::Player(const glm::vec3& startPos)
        : position(startPos), forward(0, 0, -1), velocity(0),
          yaw(0), pitch(0), health(100.0f), maxHealth(100.0f),
          ammo(120), kills(0)
    {
    }

    void Player::update(float deltaTime)
    {
        // Apply velocity damping
        velocity *= 0.95f;
    }

    void Player::render(Renderer* renderer) const
    {
        // First-person view - no rendering of player model
        // The world is rendered from the player's perspective
    }

    void Player::move(const glm::vec3& direction)
    {
        position += direction;
    }

    void Player::setRotation(float newYaw, float newPitch)
    {
        yaw = newYaw;
        pitch = newPitch;

        // Update forward direction
        forward.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        forward.y = sin(glm::radians(pitch));
        forward.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    }

    void Player::takeDamage(float damage)
    {
        health -= damage;
        if (health < 0) health = 0;
        std::cout << "Player health: " << health << "/" << maxHealth << std::endl;
    }

    void Player::heal(float amount)
    {
        health += amount;
        if (health > maxHealth) health = maxHealth;
    }
}
