#pragma once

#include "Enemy.hpp"

class Player;

// Chaser - enemy that follows the player when in range
class Chaser : public Enemy {
public:
    Chaser(sf::Vector2f position);

    void setTarget(Player* player) { m_target = player; }

protected:
    void updateAI(float deltaTime, const std::vector<Platform>& platforms) override;

private:
    Player* m_target;
    float m_detectionRange;
    float m_chaseSpeed;
    float m_idleSpeed;

    static constexpr float DEFAULT_DETECTION_RANGE = 300.0f;
    static constexpr float CHASE_SPEED = 150.0f;
    static constexpr float IDLE_SPEED = 40.0f;
};
