#pragma once

#include "../core/GameObject.hpp"
#include "../core/Health.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

class Platform;

class Player : public GameObject {
public:
    explicit Player(sf::Vector2f position);

    void handleInput();
    void update(float deltaTime, const std::vector<Platform>& platforms);
    void draw(sf::RenderWindow& window) const override;

    sf::Vector2f getCenter() const;
    sf::FloatRect getBounds() const override;

    // Health access
    Health& getHealth() { return m_health; }
    const Health& getHealth() const { return m_health; }
    bool isDead() const { return m_health.isDead(); }

    // Respawn
    void respawn(sf::Vector2f position);

private:
    void applyGravity(float deltaTime);
    void handleCollisions(const std::vector<Platform>& platforms);

    sf::RectangleShape m_shape;
    sf::Vector2f m_velocity;
    Health m_health;
    sf::Vector2f m_spawnPosition;
    
    bool m_isOnGround;
    bool m_isJumping;
    int m_jumpCount;
    bool m_jumpKeyReleased;

    // Physics constants
    static constexpr float MOVE_SPEED = 300.0f;
    static constexpr float JUMP_FORCE = -500.0f;
    static constexpr float GRAVITY = 1200.0f;
    static constexpr float MAX_FALL_SPEED = 800.0f;
    static constexpr int MAX_JUMPS = 2;

    // Player size
    static constexpr float WIDTH = 40.0f;
    static constexpr float HEIGHT = 40.0f;
};
