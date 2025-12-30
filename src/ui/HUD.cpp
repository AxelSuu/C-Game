#include "HUD.hpp"
#include "../sprites/Player.hpp"
#include "../core/ScoreManager.hpp"
#include <stdexcept>

HUD::HUD(sf::RenderWindow& window, const std::string& fontPath)
    : m_window(window)
    , m_currentHealth(0)
    , m_maxHealth(0)
    , m_score(0)
    , m_highScore(0)
    , m_combo(0)
    , m_coins(0)
{
    if (!m_font.openFromFile(fontPath)) {
        throw std::runtime_error("Failed to load font for HUD: " + fontPath);
    }

    // Setup health bar background
    m_healthBarBackground.setSize({HEALTH_BAR_WIDTH, HEALTH_BAR_HEIGHT});
    m_healthBarBackground.setFillColor(sf::Color(60, 60, 60, 200));
    m_healthBarBackground.setOutlineColor(sf::Color::White);
    m_healthBarBackground.setOutlineThickness(2.0f);

    // Setup health bar fill
    m_healthBarFill.setSize({HEALTH_BAR_WIDTH, HEALTH_BAR_HEIGHT});
    m_healthBarFill.setFillColor(sf::Color(200, 50, 50));

    // Setup health text
    m_healthText.emplace(m_font, "HP", 18);
    m_healthText->setFillColor(sf::Color::White);

    // Setup score text
    m_scoreText.emplace(m_font, "Score: 0", 24);
    m_scoreText->setFillColor(sf::Color::White);

    // Setup high score text
    m_highScoreText.emplace(m_font, "Best: 0", 16);
    m_highScoreText->setFillColor(sf::Color(180, 180, 180));

    // Setup combo text
    m_comboText.emplace(m_font, "", 20);
    m_comboText->setFillColor(sf::Color::Yellow);

    // Setup coin text
    m_coinText.emplace(m_font, "Coins: 0", 20);
    m_coinText->setFillColor(sf::Color(255, 215, 0));  // Gold color
}

void HUD::update(const Player& player, int coinsCollected)
{
    const Health& health = player.getHealth();
    m_currentHealth = health.getHealth();
    m_maxHealth = health.getMaxHealth();

    ScoreManager& scoreManager = ScoreManager::getInstance();
    m_score = scoreManager.getScore();
    m_highScore = scoreManager.getHighScore();
    m_combo = scoreManager.getCombo();
    m_coins = coinsCollected;
}

void HUD::draw()
{
    // Save current view and switch to default for UI
    sf::View currentView = m_window.getView();
    m_window.setView(m_window.getDefaultView());

    drawHealthBar();
    drawScore();
    drawCombo();
    drawCoins();

    // Restore game view
    m_window.setView(currentView);
}

void HUD::drawHealthBar()
{
    // Position health bar in top-left
    sf::Vector2f position(PADDING, PADDING);

    m_healthBarBackground.setPosition(position);
    m_window.draw(m_healthBarBackground);

    // Calculate fill width based on health percentage
    float healthPercent = (m_maxHealth > 0) ? 
        static_cast<float>(m_currentHealth) / static_cast<float>(m_maxHealth) : 0.0f;
    
    // Color based on health level
    if (healthPercent > 0.6f) {
        m_healthBarFill.setFillColor(sf::Color(50, 200, 50)); // Green
    } else if (healthPercent > 0.3f) {
        m_healthBarFill.setFillColor(sf::Color(200, 200, 50)); // Yellow
    } else {
        m_healthBarFill.setFillColor(sf::Color(200, 50, 50)); // Red
    }

    m_healthBarFill.setSize({HEALTH_BAR_WIDTH * healthPercent, HEALTH_BAR_HEIGHT});
    m_healthBarFill.setPosition(position);
    m_window.draw(m_healthBarFill);

    // Draw health text
    m_healthText->setString("HP: " + std::to_string(m_currentHealth) + "/" + std::to_string(m_maxHealth));
    m_healthText->setPosition({position.x + 5.0f, position.y + 2.0f});
    m_window.draw(*m_healthText);
}

void HUD::drawScore()
{
    sf::Vector2u windowSize = m_window.getSize();

    // Score in top-right
    m_scoreText->setString("Score: " + std::to_string(m_score));
    sf::FloatRect scoreBounds = m_scoreText->getLocalBounds();
    m_scoreText->setPosition({
        static_cast<float>(windowSize.x) - scoreBounds.size.x - PADDING,
        PADDING
    });
    m_window.draw(*m_scoreText);

    // High score below current score
    m_highScoreText->setString("Best: " + std::to_string(m_highScore));
    sf::FloatRect highBounds = m_highScoreText->getLocalBounds();
    m_highScoreText->setPosition({
        static_cast<float>(windowSize.x) - highBounds.size.x - PADDING,
        PADDING + 30.0f
    });
    m_window.draw(*m_highScoreText);
}

void HUD::drawCombo()
{
    if (m_combo < 2) {
        return; // Don't show combo for less than 2
    }

    sf::Vector2u windowSize = m_window.getSize();
    float centerX = static_cast<float>(windowSize.x) / 2.0f;

    m_comboText->setString("Combo x" + std::to_string(m_combo));
    sf::FloatRect comboBounds = m_comboText->getLocalBounds();
    m_comboText->setPosition({
        centerX - comboBounds.size.x / 2.0f,
        PADDING
    });
    m_window.draw(*m_comboText);
}

void HUD::drawCoins()
{
    // Draw coin count below health bar
    m_coinText->setString("Coins: " + std::to_string(m_coins));
    m_coinText->setPosition({PADDING, PADDING + HEALTH_BAR_HEIGHT + 10.0f});
    m_window.draw(*m_coinText);
}
