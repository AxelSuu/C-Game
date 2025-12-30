#pragma once

#include "State.hpp"
#include <SFML/Graphics.hpp>

class PauseState : public State {
public:
    explicit PauseState(sf::RenderWindow& window);

    std::string run() override;
    void onEnter() override;

private:
    void processEvents();
    void render();

    sf::Font m_font;

    int m_selectedOption;
    bool m_running;
    std::string m_nextState;

    static constexpr int OPTION_RESUME = 0;
    static constexpr int OPTION_MENU = 1;
    static constexpr int OPTION_QUIT = 2;
    static constexpr int OPTION_COUNT = 3;
};
