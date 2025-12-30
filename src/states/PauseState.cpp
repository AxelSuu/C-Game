#include "PauseState.hpp"
#include <stdexcept>

PauseState::PauseState(sf::RenderWindow& window)
    : State(window)
    , m_selectedOption(OPTION_RESUME)
    , m_running(true)
    , m_nextState("")
{
    if (!m_font.openFromFile("../src/font/Outfit-Regular.ttf")) {
        throw std::runtime_error("Failed to load font: src/font/Outfit-Regular.ttf");
    }
}

void PauseState::onEnter()
{
    m_selectedOption = OPTION_RESUME;
    m_running = true;
    m_nextState = "";
}

std::string PauseState::run()
{
    while (m_window.isOpen() && m_running) {
        processEvents();
        render();
    }

    if (!m_window.isOpen()) {
        return "quit";
    }
    return m_nextState;
}

void PauseState::processEvents()
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
                    if (m_selectedOption == OPTION_RESUME) {
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
                    // Escape in pause menu resumes the game
                    m_nextState = "game";
                    m_running = false;
                    break;

                default:
                    break;
            }
        }
    }
}

void PauseState::render()
{
    // Don't clear - keep the game visible behind the pause overlay
    m_window.setView(m_window.getDefaultView());

    sf::Vector2u windowSize = m_window.getSize();
    float centerX = static_cast<float>(windowSize.x) / 2.0f;
    float centerY = static_cast<float>(windowSize.y) / 2.0f;

    // Semi-transparent overlay
    sf::RectangleShape overlay({static_cast<float>(windowSize.x), static_cast<float>(windowSize.y)});
    overlay.setPosition({0.0f, 0.0f});
    overlay.setFillColor(sf::Color(0, 0, 0, 150));
    m_window.draw(overlay);

    // Pause box
    sf::RectangleShape pauseBox({300.0f, 300.0f});
    pauseBox.setPosition({centerX - 150.0f, centerY - 150.0f});
    pauseBox.setFillColor(sf::Color(40, 40, 60, 230));
    pauseBox.setOutlineColor(sf::Color::White);
    pauseBox.setOutlineThickness(3.0f);
    m_window.draw(pauseBox);

    // "PAUSED" title
    sf::Text pausedText(m_font, "PAUSED", 42);
    pausedText.setFillColor(sf::Color::White);
    pausedText.setOutlineColor(sf::Color(80, 80, 120));
    pausedText.setOutlineThickness(2.0f);
    sf::FloatRect pausedBounds = pausedText.getLocalBounds();
    pausedText.setPosition({centerX - pausedBounds.size.x / 2.0f, centerY - 130.0f});
    m_window.draw(pausedText);

    // Menu options
    float optionY = centerY - 40.0f;
    float optionSpacing = 55.0f;

    const char* optionNames[] = {"Resume", "Menu", "Quit"};
    sf::Color selectedColors[] = {sf::Color(100, 150, 100), sf::Color(100, 100, 150), sf::Color(150, 100, 100)};
    sf::Color outlineColors[] = {sf::Color::Green, sf::Color::Cyan, sf::Color::Red};

    for (int i = 0; i < OPTION_COUNT; i++) {
        sf::RectangleShape option({180.0f, 40.0f});
        option.setPosition({centerX - 90.0f, optionY + i * optionSpacing});
        option.setFillColor(m_selectedOption == i ? selectedColors[i] : sf::Color(60, 60, 80));
        option.setOutlineColor(m_selectedOption == i ? outlineColors[i] : sf::Color::White);
        option.setOutlineThickness(2.0f);
        m_window.draw(option);

        // Option text
        sf::Text optionText(m_font, optionNames[i], 24);
        optionText.setFillColor(sf::Color::White);
        sf::FloatRect textBounds = optionText.getLocalBounds();
        optionText.setPosition({centerX - textBounds.size.x / 2.0f, optionY + i * optionSpacing + 6.0f});
        m_window.draw(optionText);

        // Selection indicator
        if (m_selectedOption == i) {
            sf::Text arrow(m_font, ">", 28);
            arrow.setFillColor(outlineColors[i]);
            arrow.setPosition({centerX - 110.0f, optionY + i * optionSpacing + 3.0f});
            m_window.draw(arrow);
        }
    }

    m_window.display();
}
