#include "Jumper.hpp"

Jumper::Jumper(sf::Vector2f position)
    : Enemy(position, {28.0f, 28.0f}, 1)
    , m_jumpTimer(0.0f)
    , m_direction(1.0f)
{
    m_shape.setFillColor(sf::Color(80, 180, 80));
    m_scoreValue = 120;
    m_damage = 1;
}

void Jumper::updateAI(float deltaTime, const std::vector<Platform>& /*platforms*/)
{
    m_jumpTimer += deltaTime;

    // Horizontal movement
    m_velocity.x = MOVE_SPEED * m_direction;

    // Jump periodically when on ground
    if (m_isOnGround && m_jumpTimer >= JUMP_INTERVAL) {
        m_velocity.y = JUMP_FORCE;
        m_jumpTimer = 0.0f;
        m_isOnGround = false;

        // Randomly change direction sometimes
        if (rand() % 3 == 0) {
            m_direction = -m_direction;
        }
    }
}
