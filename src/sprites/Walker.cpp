#include "Walker.hpp"
#include "Platform.hpp"

Walker::Walker(sf::Vector2f position)
    : Enemy(position, {35.0f, 35.0f}, 1)
    , m_direction(1.0f)
{
    m_shape.setFillColor(sf::Color(180, 80, 80));
    m_scoreValue = 100;
    m_damage = 1;
}

void Walker::updateAI(float /*deltaTime*/, const std::vector<Platform>& platforms)
{
    // Simple walking AI
    m_velocity.x = WALK_SPEED * m_direction;

    // Check for edge detection - don't walk off platforms
    if (m_isOnGround) {
        sf::Vector2f checkPos = m_shape.getPosition();
        checkPos.x += (m_direction > 0 ? m_shape.getSize().x + 5.0f : -5.0f);
        checkPos.y += m_shape.getSize().y + 5.0f;

        bool foundGround = false;
        for (const auto& platform : platforms) {
            sf::FloatRect bounds = platform.getBounds();
            if (checkPos.x >= bounds.position.x && 
                checkPos.x <= bounds.position.x + bounds.size.x &&
                checkPos.y >= bounds.position.y && 
                checkPos.y <= bounds.position.y + bounds.size.y) {
                foundGround = true;
                break;
            }
        }

        if (!foundGround) {
            m_direction = -m_direction;
            m_velocity.x = WALK_SPEED * m_direction;
        }
    }
}
