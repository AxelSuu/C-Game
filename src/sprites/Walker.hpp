#pragma once

#include "Enemy.hpp"

// Walker - simple patrolling enemy that walks back and forth
class Walker : public Enemy {
public:
    Walker(sf::Vector2f position);

protected:
    void updateAI(float deltaTime, const std::vector<Platform>& platforms) override;

private:
    float m_direction;
    static constexpr float WALK_SPEED = 80.0f;
};
