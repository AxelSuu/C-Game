#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class StateManager;

class State {
public:
    explicit State(sf::RenderWindow& window);
    virtual ~State() = default;

    // Main state loop - returns the name of the next state, or empty string to quit
    virtual std::string run() = 0;

    // Optional: called when state becomes active
    virtual void onEnter() {}

    // Optional: called when state is about to be replaced
    virtual void onExit() {}

protected:
    sf::RenderWindow& m_window;
};
