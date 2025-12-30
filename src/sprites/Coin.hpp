#pragma once

#include "../core/GameObject.hpp"
#include <SFML/Graphics.hpp>

class Coin : public GameObject {
public:
    explicit Coin(sf::Vector2f position, int value = 10);

    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) const override;

    sf::FloatRect getBounds() const override;

    // Collect the coin
    void collect();
    bool isCollected() const { return m_collected; }
    int getValue() const { return m_value; }

private:
    sf::CircleShape m_shape;
    int m_value;
    bool m_collected;

    // Animation
    float m_animationTime;
    float m_baseY;

    static constexpr float RADIUS = 12.0f;
    static constexpr float BOB_SPEED = 3.0f;
    static constexpr float BOB_AMOUNT = 4.0f;
};
