#pragma once

#include "../core/GameObject.hpp"
#include <SFML/Graphics.hpp>

class Platform : public GameObject {
public:
    Platform(sf::Vector2f position, sf::Vector2f size, sf::Color color = sf::Color(100, 100, 100));

    void draw(sf::RenderWindow& window) const override;

    sf::FloatRect getBounds() const override;
    sf::Vector2f getSize() const;

private:
    sf::RectangleShape m_shape;
    sf::Vector2f m_size;
};
