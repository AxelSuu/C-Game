#include "Enemy.hpp"
#include "Platform.hpp"
#include "Player.hpp"
#include "../core/ScoreManager.hpp"

Enemy::Enemy(sf::Vector2f position, sf::Vector2f size, int health)
    : GameObject(position)
    , m_velocity(0.0f, 0.0f)
    , m_health(health)
    , m_scoreValue(100)
    , m_damage(1)
    , m_isOnGround(false)
{
    m_shape.setSize(size);
    m_shape.setPosition(m_position);
    m_shape.setFillColor(sf::Color::Red);
    m_shape.setOutlineColor(sf::Color::White);
    m_shape.setOutlineThickness(1.0f);
}

void Enemy::update(float deltaTime, const std::vector<Platform>& platforms)
{
    if (isDead()) return;

    m_health.update(deltaTime);
    updateAI(deltaTime, platforms);
    applyGravity(deltaTime);

    // Apply movement
    m_shape.move({m_velocity.x * deltaTime, 0.0f});
    handleCollisions(platforms);

    m_shape.move({0.0f, m_velocity.y * deltaTime});
    handleCollisions(platforms);

    m_position = m_shape.getPosition();
}

void Enemy::updateAI(float /*deltaTime*/, const std::vector<Platform>& /*platforms*/)
{
    // Base implementation does nothing - override in subclasses
}

void Enemy::applyGravity(float deltaTime)
{
    m_velocity.y += GRAVITY * deltaTime;
    if (m_velocity.y > MAX_FALL_SPEED) {
        m_velocity.y = MAX_FALL_SPEED;
    }
}

void Enemy::handleCollisions(const std::vector<Platform>& platforms)
{
    m_isOnGround = false;

    for (const auto& platform : platforms) {
        sf::FloatRect enemyBounds = getBounds();
        sf::FloatRect platformBounds = platform.getBounds();

        auto intersection = enemyBounds.findIntersection(platformBounds);
        if (!intersection) {
            continue;
        }

        sf::FloatRect overlap = intersection.value();

        if (overlap.size.x < overlap.size.y) {
            // Horizontal collision - reverse direction
            if (enemyBounds.position.x < platformBounds.position.x) {
                m_shape.move({-overlap.size.x, 0.0f});
            } else {
                m_shape.move({overlap.size.x, 0.0f});
            }
            m_velocity.x = -m_velocity.x; // Reverse direction
        } else {
            // Vertical collision
            if (enemyBounds.position.y < platformBounds.position.y) {
                m_shape.move({0.0f, -overlap.size.y});
                m_velocity.y = 0.0f;
                m_isOnGround = true;
            } else {
                m_shape.move({0.0f, overlap.size.y});
                m_velocity.y = 0.0f;
            }
        }
    }
}

void Enemy::draw(sf::RenderWindow& window) const
{
    if (!isDead()) {
        window.draw(m_shape);
    }
}

sf::FloatRect Enemy::getBounds() const
{
    return m_shape.getGlobalBounds();
}

void Enemy::onPlayerCollision(Player& player)
{
    // Default: damage the player
    player.getHealth().damage(m_damage);
}

void Enemy::onStomped(Player& player)
{
    // Default: die and give score
    m_health.damage(m_health.getMaxHealth()); // Kill instantly
    ScoreManager::getInstance().addScore(m_scoreValue);
    ScoreManager::getInstance().incrementCombo();
}
