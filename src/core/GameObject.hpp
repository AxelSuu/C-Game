#pragma once

#include <SFML/Graphics.hpp>

class GameObject {
public:
    explicit GameObject(sf::Vector2f position = {0.0f, 0.0f});
    virtual ~GameObject() = default;

    // Core methods - can be overridden
    virtual void update(float deltaTime);
    virtual void draw(sf::RenderWindow& window) const = 0;

    // Position management
    sf::Vector2f getPosition() const;
    void setPosition(sf::Vector2f position);
    void move(sf::Vector2f offset);

    // Bounds for collision
    virtual sf::FloatRect getBounds() const = 0;

    // Visibility
    bool isVisible() const { return m_visible; }
    void setVisible(bool visible) { m_visible = visible; }

    // Active state (for update logic)
    bool isActive() const { return m_active; }
    void setActive(bool active) { m_active = active; }

protected:
    sf::Vector2f m_position;
    bool m_visible;
    bool m_active;
};
