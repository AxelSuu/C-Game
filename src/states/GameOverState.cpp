#include "GameOverState.hpp"
#include "../core/ScoreManager.hpp"
#include <stdexcept>

GameOverState::GameOverState(sf::RenderWindow& window)
    : State(window)
    , m_selectedOption(OPTION_RETRY)
    , m_running(true)
    , m_nextState("")
    , m_finalScore(0)
    , m_highScore(0)
{
    if (!m_font.openFromFile("../src/font/Outfit-Regular.ttf")) {
        throw std::runtime_error("Failed to load font: src/font/Outfit-Regular.ttf");
    }
}

void GameOverState::onEnter()
{
    m_selectedOption = OPTION_RETRY;
    m_running = true;
    m_nextState = "";

    // Capture the final score when entering game over
    auto& scoreManager = ScoreManager::getInstance();
    m_finalScore = scoreManager.getScore();
    m_highScore = scoreManager.getHighScore();
}

std::string GameOverState::run()
{
    sf::Clock clock;

    while (m_window.isOpen() && m_running) {
        float deltaTime = clock.restart().asSeconds();
        if (deltaTime > 0.1f) deltaTime = 0.1f;

        processEvents();
        update(deltaTime);
        render();
    }

    if (!m_window.isOpen()) {
        return "quit";
    }
    return m_nextState;
}

void GameOverState::processEvents()
{
    while (const std::optional event = m_window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            m_window.close();
        }

        if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            switch (keyPressed->code) {
                case sf::Keyboard::Key::Up:
                case sf::Keyboard::Key::W:
                    m_selectedOption = (m_selectedOption - 1 + OPTION_COUNT) % OPTION_COUNT;
                    break;

                case sf::Keyboard::Key::Down:
                case sf::Keyboard::Key::S:
                    m_selectedOption = (m_selectedOption + 1) % OPTION_COUNT;
                    break;

                case sf::Keyboard::Key::Enter:
                case sf::Keyboard::Key::Space:
                    if (m_selectedOption == OPTION_RETRY) {
                        m_nextState = "game";
                        m_running = false;
                    } else if (m_selectedOption == OPTION_MENU) {
                        m_nextState = "menu";
                        m_running = false;
                    } else if (m_selectedOption == OPTION_QUIT) {
                        m_nextState = "quit";
                        m_running = false;
                    }
                    break;

                case sf::Keyboard::Key::Escape:
                    m_nextState = "menu";
                    m_running = false;
                    break;

                default:
                    break;
            }
        }
    }
}

void GameOverState::update(float /*deltaTime*/)
{
    // Nothing to update
}

void GameOverState::render()
{
    m_window.clear(sf::Color(40, 20, 20));

    // Reset to default view for UI
    m_window.setView(m_window.getDefaultView());

    sf::Vector2u windowSize = m_window.getSize();
    float centerX = static_cast<float>(windowSize.x) / 2.0f;
    float centerY = static_cast<float>(windowSize.y) / 2.0f;

    // Draw "GAME OVER" title
    sf::Text titleText(m_font, "GAME OVER", 72);
    titleText.setFillColor(sf::Color(200, 50, 50));
    sf::FloatRect titleBounds = titleText.getLocalBounds();
    titleText.setPosition({centerX - titleBounds.size.x / 2.0f, 80.0f});
    m_window.draw(titleText);

    // Draw final score
    sf::Text scoreText(m_font, "Score: " + std::to_string(m_finalScore), 36);
    scoreText.setFillColor(sf::Color::White);
    sf::FloatRect scoreBounds = scoreText.getLocalBounds();
    scoreText.setPosition({centerX - scoreBounds.size.x / 2.0f, 180.0f});
    m_window.draw(scoreText);

    // Draw high score
    sf::Text highScoreText(m_font, "High Score: " + std::to_string(m_highScore), 28);
    if (m_finalScore >= m_highScore && m_finalScore > 0) {
        highScoreText.setFillColor(sf::Color(255, 215, 0)); // Gold for new high score
        highScoreText.setString("NEW HIGH SCORE: " + std::to_string(m_highScore));
    } else {
        highScoreText.setFillColor(sf::Color(180, 180, 180));
    }
    sf::FloatRect highScoreBounds = highScoreText.getLocalBounds();
    highScoreText.setPosition({centerX - highScoreBounds.size.x / 2.0f, 230.0f});
    m_window.draw(highScoreText);

    // Menu options
    const char* options[] = {"RETRY", "MAIN MENU", "QUIT"};
    float startY = centerY + 50.0f;
    float spacing = 60.0f;

    for (int i = 0; i < OPTION_COUNT; ++i) {
        sf::Text optionText(m_font, options[i], 32);

        if (i == m_selectedOption) {
            optionText.setFillColor(sf::Color(255, 100, 100));
            optionText.setString("> " + std::string(options[i]) + " <");
        } else {
            optionText.setFillColor(sf::Color(150, 150, 150));
        }

        sf::FloatRect optionBounds = optionText.getLocalBounds();
        optionText.setPosition({centerX - optionBounds.size.x / 2.0f, startY + i * spacing});
        m_window.draw(optionText);
    }

    // Instructions
    sf::Text instructionText(m_font, "Use W/S or Arrow Keys to navigate, Enter to select", 18);
    instructionText.setFillColor(sf::Color(120, 120, 120));
    sf::FloatRect instructionBounds = instructionText.getLocalBounds();
    instructionText.setPosition({centerX - instructionBounds.size.x / 2.0f, 
                                  static_cast<float>(windowSize.y) - 50.0f});
    m_window.draw(instructionText);

    m_window.display();
}
