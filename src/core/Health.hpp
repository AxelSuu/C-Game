#pragma once

#include <functional>

class Health {
public:
    using Callback = std::function<void()>;

    explicit Health(int maxHealth);

    // Health manipulation
    void damage(int amount);
    void heal(int amount);
    void setHealth(int health);
    void reset();

    // Getters
    int getHealth() const { return m_currentHealth; }
    int getMaxHealth() const { return m_maxHealth; }
    float getPercentage() const;
    bool isDead() const { return m_currentHealth <= 0; }
    bool isFullHealth() const { return m_currentHealth >= m_maxHealth; }

    // Callbacks
    void setOnDeath(Callback callback) { m_onDeath = std::move(callback); }
    void setOnDamage(Callback callback) { m_onDamage = std::move(callback); }
    void setOnHeal(Callback callback) { m_onHeal = std::move(callback); }

    // Invincibility frames
    void setInvincibilityTime(float seconds) { m_invincibilityDuration = seconds; }
    void update(float deltaTime);
    bool isInvincible() const { return m_invincibilityTimer > 0.0f; }

private:
    int m_currentHealth;
    int m_maxHealth;

    float m_invincibilityTimer;
    float m_invincibilityDuration;

    Callback m_onDeath;
    Callback m_onDamage;
    Callback m_onHeal;
};
