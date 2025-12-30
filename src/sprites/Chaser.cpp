#include "Chaser.hpp"
#include "Player.hpp"
#include <cmath>

Chaser::Chaser(sf::Vector2f position)
    : Enemy(position, {30.0f, 40.0f}, 1)
    , m_target(nullptr)
    , m_detectionRange(DEFAULT_DETECTION_RANGE)
    , m_chaseSpeed(CHASE_SPEED)
    , m_idleSpeed(IDLE_SPEED)
{
    m_shape.setFillColor(sf::Color(200, 50, 150));
    m_scoreValue = 150;
    m_damage = 1;
}

void Chaser::updateAI(float /*deltaTime*/, const std::vector<Platform>& /*platforms*/)
{
    if (!m_target) {
        m_velocity.x = 0.0f;
        return;
    }

    sf::Vector2f targetPos = m_target->getCenter();
    sf::Vector2f myPos = m_shape.getPosition() + m_shape.getSize() / 2.0f;

    float dx = targetPos.x - myPos.x;
    float dy = targetPos.y - myPos.y;
    float distance = std::sqrt(dx * dx + dy * dy);

    if (distance < m_detectionRange) {
        // Chase the player
        if (std::abs(dx) > 10.0f) {
            m_velocity.x = (dx > 0 ? 1.0f : -1.0f) * m_chaseSpeed;
        } else {
            m_velocity.x = 0.0f;
        }

        // Visual feedback when chasing
        m_shape.setFillColor(sf::Color(255, 50, 100));
    } else {
        // Idle patrol
        m_velocity.x = m_idleSpeed * (static_cast<int>(myPos.x / 100) % 2 == 0 ? 1.0f : -1.0f);
        m_shape.setFillColor(sf::Color(200, 50, 150));
    }
}
