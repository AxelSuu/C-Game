#pragma once

#include "State.hpp"
#include <SFML/Graphics.hpp>

class MenuState : public State {
public:
    explicit MenuState(sf::RenderWindow& window);

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

    static constexpr int OPTION_PLAY = 0;
    static constexpr int OPTION_QUIT = 1;
    static constexpr int OPTION_COUNT = 2;
};
