#pragma once

#include <SFML/Graphics.hpp>
#include <optional>

class Player;

class HUD {
public:
    HUD(sf::RenderWindow& window, const std::string& fontPath);

    void update(const Player& player, int coinsCollected = 0);
    void draw();

private:
    void drawHealthBar();
    void drawScore();
    void drawCombo();
    void drawCoins();

    sf::RenderWindow& m_window;
    sf::Font m_font;

    // Health bar
    sf::RectangleShape m_healthBarBackground;
    sf::RectangleShape m_healthBarFill;
    std::optional<sf::Text> m_healthText;

    // Score
    std::optional<sf::Text> m_scoreText;
    std::optional<sf::Text> m_highScoreText;

    // Combo
    std::optional<sf::Text> m_comboText;

    // Coins
    std::optional<sf::Text> m_coinText;

    // Cached values
    int m_currentHealth;
    int m_maxHealth;
    int m_score;
    int m_highScore;
    int m_combo;
    int m_coins;

    // Layout constants
    static constexpr float PADDING = 20.0f;
    static constexpr float HEALTH_BAR_WIDTH = 200.0f;
    static constexpr float HEALTH_BAR_HEIGHT = 25.0f;
};
