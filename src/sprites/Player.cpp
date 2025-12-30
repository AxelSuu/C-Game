#include "Player.hpp"
#include "Platform.hpp"

Player::Player(sf::Vector2f position)
    : GameObject(position)
    , m_velocity(0.0f, 0.0f)
    , m_health(3)  // 3 health points
    , m_spawnPosition(position)
    , m_isOnGround(false)
    , m_isJumping(false)
    , m_jumpCount(0)
    , m_jumpKeyReleased(true)
{
    m_health.setInvincibilityTime(1.5f);
    m_shape.setSize({WIDTH, HEIGHT});
    m_shape.setPosition(m_position);
    m_shape.setFillColor(sf::Color::Green);
    m_shape.setOutlineColor(sf::Color::White);
    m_shape.setOutlineThickness(2.0f);
}

void Player::handleInput()
{
    m_velocity.x = 0.0f;

    // Horizontal movement
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || 
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        m_velocity.x = -MOVE_SPEED;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || 
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        m_velocity.x = MOVE_SPEED;
    }

    // Jumping with double jump support
    bool jumpKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) || 
                          sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) ||
                          sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space);

    if (jumpKeyPressed && m_jumpKeyReleased && m_jumpCount < MAX_JUMPS) {
        m_velocity.y = JUMP_FORCE;
        m_isOnGround = false;
        m_isJumping = true;
        m_jumpCount++;
        m_jumpKeyReleased = false;
    }

    if (!jumpKeyPressed) {
        m_jumpKeyReleased = true;
    }
}

void Player::update(float deltaTime, const std::vector<Platform>& platforms)
{
    // Update health invincibility timer
    m_health.update(deltaTime);

    applyGravity(deltaTime);

    // Apply horizontal movement
    m_shape.move({m_velocity.x * deltaTime, 0.0f});
    handleCollisions(platforms);

    // Apply vertical movement
    m_shape.move({0.0f, m_velocity.y * deltaTime});
    handleCollisions(platforms);
}

void Player::applyGravity(float deltaTime)
{
    m_velocity.y += GRAVITY * deltaTime;
    if (m_velocity.y > MAX_FALL_SPEED) {
        m_velocity.y = MAX_FALL_SPEED;
    }
}

void Player::handleCollisions(const std::vector<Platform>& platforms)
{
    m_isOnGround = false;

    for (const auto& platform : platforms) {
        sf::FloatRect playerBounds = getBounds();
        sf::FloatRect platformBounds = platform.getBounds();

        if (!playerBounds.findIntersection(platformBounds)) {
            continue;
        }

        sf::FloatRect intersection = playerBounds.findIntersection(platformBounds).value();

        // Determine collision direction based on overlap
        if (intersection.size.x < intersection.size.y) {
            // Horizontal collision
            if (playerBounds.position.x < platformBounds.position.x) {
                m_shape.move({-intersection.size.x, 0.0f});
            } else {
                m_shape.move({intersection.size.x, 0.0f});
            }
            m_velocity.x = 0.0f;
        } else {
            // Vertical collision
            if (playerBounds.position.y < platformBounds.position.y) {
                // Landing on top
                m_shape.move({0.0f, -intersection.size.y});
                m_velocity.y = 0.0f;
                m_isOnGround = true;
                m_isJumping = false;
                m_jumpCount = 0;
            } else {
                // Hitting from below
                m_shape.move({0.0f, intersection.size.y});
                m_velocity.y = 0.0f;
            }
        }
    }
}

void Player::draw(sf::RenderWindow& window) const
{
    // Flash when invincible
    if (m_health.isInvincible()) {
        // Create a copy to modify alpha
        sf::RectangleShape flashShape = m_shape;
        sf::Color color = flashShape.getFillColor();
        // Flicker effect
        color.a = static_cast<std::uint8_t>((static_cast<int>(m_health.getPercentage() * 1000) % 2) ? 100 : 255);
        flashShape.setFillColor(color);
        window.draw(flashShape);
    } else {
        window.draw(m_shape);
    }
}

void Player::respawn(sf::Vector2f position)
{
    m_shape.setPosition(position);
    m_position = position;
    m_velocity = {0.0f, 0.0f};
    m_health.reset();
    m_isOnGround = false;
    m_isJumping = false;
}

sf::Vector2f Player::getCenter() const
{
    return m_shape.getPosition() + sf::Vector2f(WIDTH / 2.0f, HEIGHT / 2.0f);
}

sf::FloatRect Player::getBounds() const
{
    return m_shape.getGlobalBounds();
}
