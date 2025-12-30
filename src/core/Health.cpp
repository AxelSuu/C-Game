#include "Health.hpp"
#include <algorithm>

Health::Health(int maxHealth)
    : m_currentHealth(maxHealth)
    , m_maxHealth(maxHealth)
    , m_invincibilityTimer(0.0f)
    , m_invincibilityDuration(1.0f)
{
}

void Health::damage(int amount)
{
    if (isDead() || isInvincible() || amount <= 0) {
        return;
    }

    m_currentHealth = std::max(0, m_currentHealth - amount);
    m_invincibilityTimer = m_invincibilityDuration;

    if (m_onDamage) {
        m_onDamage();
    }

    if (isDead() && m_onDeath) {
        m_onDeath();
    }
}

void Health::heal(int amount)
{
    if (isDead() || amount <= 0) {
        return;
    }

    int oldHealth = m_currentHealth;
    m_currentHealth = std::min(m_maxHealth, m_currentHealth + amount);

    if (m_currentHealth > oldHealth && m_onHeal) {
        m_onHeal();
    }
}

void Health::setHealth(int health)
{
    m_currentHealth = std::clamp(health, 0, m_maxHealth);
}

void Health::reset()
{
    m_currentHealth = m_maxHealth;
    m_invincibilityTimer = 0.0f;
}

float Health::getPercentage() const
{
    if (m_maxHealth <= 0) return 0.0f;
    return static_cast<float>(m_currentHealth) / static_cast<float>(m_maxHealth);
}

void Health::update(float deltaTime)
{
    if (m_invincibilityTimer > 0.0f) {
        m_invincibilityTimer -= deltaTime;
    }
}
