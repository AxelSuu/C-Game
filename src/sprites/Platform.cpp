#include "Platform.hpp"

Platform::Platform(sf::Vector2f position, sf::Vector2f size, sf::Color color)
    : GameObject(position)
    , m_size(size)
{
    m_shape.setPosition(m_position);
    m_shape.setSize(size);
    m_shape.setFillColor(color);
    m_shape.setOutlineColor(sf::Color::White);
    m_shape.setOutlineThickness(1.0f);
}

void Platform::draw(sf::RenderWindow& window) const
{
    window.draw(m_shape);
}

sf::FloatRect Platform::getBounds() const
{
    return m_shape.getGlobalBounds();
}

sf::Vector2f Platform::getSize() const
{
    return m_size;
}
