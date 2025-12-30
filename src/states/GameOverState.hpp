#pragma once

#include "State.hpp"
#include <SFML/Graphics.hpp>

class GameOverState : public State {
public:
    explicit GameOverState(sf::RenderWindow& window);

    std::string run() override;
    void onEnter() override;

private:
    void processEvents();
    void update(float deltaTime);
    void render();

    sf::Font m_font;

    int m_selectedOption;
    bool m_running;
    std::string m_nextState;

    int m_finalScore;
    int m_highScore;

    static constexpr int OPTION_RETRY = 0;
    static constexpr int OPTION_MENU = 1;
    static constexpr int OPTION_QUIT = 2;
    static constexpr int OPTION_COUNT = 3;
};
