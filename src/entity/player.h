#ifndef FPS_PLAYER_H
#define FPS_PLAYER_H

#include <glm/glm.hpp>
#include "../graphics/renderer.h"

namespace FPS
{
    class Player
    {
    public:
        Player(const glm::vec3& startPos);
        ~Player() = default;

        void update(float deltaTime);
        void render(Renderer* renderer) const;
        void move(const glm::vec3& direction);
        void setRotation(float yaw, float pitch);
        void takeDamage(float damage);
        void heal(float amount);

        glm::vec3 getPosition() const { return position; }
        glm::vec3 getForward() const { return forward; }
        float getHealth() const { return health; }
        float getMaxHealth() const { return maxHealth; }
        int getAmmo() const { return ammo; }
        int getKills() const { return kills; }

    private:
        glm::vec3 position;
        glm::vec3 forward;
        glm::vec3 velocity;
        float yaw, pitch;
        float health;
        float maxHealth;
        int ammo;
        int kills;
    };
}

#endif
