#pragma once

#include <SFML/Graphics.hpp>

class Camera {
public:
    Camera(sf::Vector2f viewSize);

    void setTarget(sf::Vector2f target);
    void update(float deltaTime);

    void apply(sf::RenderWindow& window) const;
    sf::View getView() const;

    // Configuration
    void setSmoothness(float smoothness);
    void setDeadzone(sf::Vector2f deadzone);
    void setBounds(sf::FloatRect bounds);
    void setUseBounds(bool useBounds);

private:
    sf::View m_view;
    sf::Vector2f m_targetPosition;
    sf::Vector2f m_currentPosition;
    sf::Vector2f m_deadzone;
    
    float m_smoothness;
    
    bool m_useBounds;
    sf::FloatRect m_bounds;

    static constexpr float DEFAULT_SMOOTHNESS = 5.0f;
};
