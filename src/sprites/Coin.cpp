#include "Coin.hpp"
#include <cmath>

Coin::Coin(sf::Vector2f position, int value)
    : GameObject(position)
    , m_value(value)
    , m_collected(false)
    , m_animationTime(0.0f)
    , m_baseY(position.y)
{
    m_shape.setRadius(RADIUS);
    m_shape.setOrigin({RADIUS, RADIUS});
    m_shape.setPosition(m_position);
    m_shape.setFillColor(sf::Color(255, 215, 0));  // Gold color
    m_shape.setOutlineColor(sf::Color(200, 160, 0));
    m_shape.setOutlineThickness(2.0f);
}

void Coin::update(float deltaTime)
{
    if (m_collected) return;

    // Bobbing animation
    m_animationTime += deltaTime * BOB_SPEED;
    float yOffset = std::sin(m_animationTime) * BOB_AMOUNT;
    m_shape.setPosition({m_position.x, m_baseY + yOffset});
}

void Coin::draw(sf::RenderWindow& window) const
{
    if (!m_collected) {
        window.draw(m_shape);
    }
}

sf::FloatRect Coin::getBounds() const
{
    return m_shape.getGlobalBounds();
}

void Coin::collect()
{
    m_collected = true;
    setActive(false);
}
