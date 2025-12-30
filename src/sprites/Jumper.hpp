#pragma once

#include "Enemy.hpp"

// Jumper - enemy that hops around
class Jumper : public Enemy {
public:
    Jumper(sf::Vector2f position);

protected:
    void updateAI(float deltaTime, const std::vector<Platform>& platforms) override;

private:
    float m_jumpTimer;
    float m_direction;

    static constexpr float JUMP_INTERVAL = 1.5f;
    static constexpr float JUMP_FORCE = -400.0f;
    static constexpr float MOVE_SPEED = 100.0f;
};
