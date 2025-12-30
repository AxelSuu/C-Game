#include "MenuState.hpp"
#include <stdexcept>

MenuState::MenuState(sf::RenderWindow& window)
    : State(window)
    , m_selectedOption(OPTION_PLAY)
    , m_running(true)
    , m_nextState("")
{
    if (!m_font.openFromFile("../src/font/Outfit-Regular.ttf")) {
        throw std::runtime_error("Failed to load font: src/font/Outfit-Regular.ttf");
    }
}

void MenuState::onEnter()
{
    m_selectedOption = OPTION_PLAY;
    m_running = true;
    m_nextState = "";
}

std::string MenuState::run()
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

void MenuState::processEvents()
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
                    if (m_selectedOption == OPTION_PLAY) {
                        m_nextState = "game";
                        m_running = false;
                    } else if (m_selectedOption == OPTION_QUIT) {
                        m_nextState = "quit";
                        m_running = false;
                    }
                    break;

                case sf::Keyboard::Key::Escape:
                    m_nextState = "quit";
                    m_running = false;
                    break;

                default:
                    break;
            }
        }
    }
}

void MenuState::update(float /*deltaTime*/)
{
    // Menu doesn't need much updating
}

void MenuState::render()
{
    m_window.clear(sf::Color(20, 20, 40));

    // Reset to default view for UI
    m_window.setView(m_window.getDefaultView());

    sf::Vector2u windowSize = m_window.getSize();
    float centerX = static_cast<float>(windowSize.x) / 2.0f;
    float centerY = static_cast<float>(windowSize.y) / 2.0f;

    // Draw title
    sf::Text titleText(m_font, "PLATFORMER", 64);
    titleText.setFillColor(sf::Color::White);
    titleText.setOutlineColor(sf::Color(80, 80, 120));
    titleText.setOutlineThickness(3.0f);
    sf::FloatRect titleBounds = titleText.getLocalBounds();
    titleText.setPosition({centerX - titleBounds.size.x / 2.0f, centerY - 180.0f});
    m_window.draw(titleText);

    // Draw menu options
    float optionY = centerY;
    float optionSpacing = 70.0f;

    // Play option
    sf::RectangleShape playOption({200.0f, 50.0f});
    playOption.setPosition({centerX - 100.0f, optionY});
    playOption.setFillColor(m_selectedOption == OPTION_PLAY ? sf::Color(100, 150, 100) : sf::Color(60, 60, 80));
    playOption.setOutlineColor(m_selectedOption == OPTION_PLAY ? sf::Color::Green : sf::Color::White);
    playOption.setOutlineThickness(2.0f);
    m_window.draw(playOption);

    sf::Text playText(m_font, "Play", 28);
    playText.setFillColor(sf::Color::White);
    sf::FloatRect playBounds = playText.getLocalBounds();
    playText.setPosition({centerX - playBounds.size.x / 2.0f, optionY + 8.0f});
    m_window.draw(playText);

    // Selection arrow for Play
    if (m_selectedOption == OPTION_PLAY) {
        sf::Text arrow(m_font, ">", 32);
        arrow.setFillColor(sf::Color::Green);
        arrow.setPosition({centerX - 120.0f, optionY + 5.0f});
        m_window.draw(arrow);
    }

    // Quit option
    sf::RectangleShape quitOption({200.0f, 50.0f});
    quitOption.setPosition({centerX - 100.0f, optionY + optionSpacing});
    quitOption.setFillColor(m_selectedOption == OPTION_QUIT ? sf::Color(150, 100, 100) : sf::Color(60, 60, 80));
    quitOption.setOutlineColor(m_selectedOption == OPTION_QUIT ? sf::Color::Red : sf::Color::White);
    quitOption.setOutlineThickness(2.0f);
    m_window.draw(quitOption);

    sf::Text quitText(m_font, "Quit", 28);
    quitText.setFillColor(sf::Color::White);
    sf::FloatRect quitBounds = quitText.getLocalBounds();
    quitText.setPosition({centerX - quitBounds.size.x / 2.0f, optionY + optionSpacing + 8.0f});
    m_window.draw(quitText);

    // Selection arrow for Quit
    if (m_selectedOption == OPTION_QUIT) {
        sf::Text arrow(m_font, ">", 32);
        arrow.setFillColor(sf::Color::Red);
        arrow.setPosition({centerX - 120.0f, optionY + optionSpacing + 5.0f});
        m_window.draw(arrow);
    }

    // Instructions
    sf::Text instructions(m_font, "Use W/S or Arrow Keys to select, Enter to confirm", 18);
    instructions.setFillColor(sf::Color(150, 150, 170));
    sf::FloatRect instrBounds = instructions.getLocalBounds();
    instructions.setPosition({centerX - instrBounds.size.x / 2.0f, centerY + 200.0f});
    m_window.draw(instructions);

    m_window.display();
}
