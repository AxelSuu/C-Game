#include "GameObject.hpp"

GameObject::GameObject(sf::Vector2f position)
    : m_position(position)
    , m_visible(true)
    , m_active(true)
{
}

void GameObject::update(float /*deltaTime*/)
{
    // Base implementation does nothing
}

sf::Vector2f GameObject::getPosition() const
{
    return m_position;
}

void GameObject::setPosition(sf::Vector2f position)
{
    m_position = position;
}

void GameObject::move(sf::Vector2f offset)
{
    m_position += offset;
}
