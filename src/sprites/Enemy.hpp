#pragma once

#include "../core/GameObject.hpp"
#include "../core/Health.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

class Platform;
class Player;

class Enemy : public GameObject {
public:
    Enemy(sf::Vector2f position, sf::Vector2f size, int health = 1);
    virtual ~Enemy() = default;

    virtual void update(float deltaTime, const std::vector<Platform>& platforms);
    void draw(sf::RenderWindow& window) const override;

    sf::FloatRect getBounds() const override;

    // Health access
    Health& getHealth() { return m_health; }
    const Health& getHealth() const { return m_health; }
    bool isDead() const { return m_health.isDead(); }

    // Combat
    virtual void onPlayerCollision(Player& player);
    virtual void onStomped(Player& player);
    int getScoreValue() const { return m_scoreValue; }

protected:
    virtual void updateAI(float deltaTime, const std::vector<Platform>& platforms);
    void applyGravity(float deltaTime);
    void handleCollisions(const std::vector<Platform>& platforms);

    sf::RectangleShape m_shape;
    sf::Vector2f m_velocity;
    Health m_health;

    int m_scoreValue;
    int m_damage;
    bool m_isOnGround;

    // Physics constants
    static constexpr float GRAVITY = 1200.0f;
    static constexpr float MAX_FALL_SPEED = 800.0f;
};
