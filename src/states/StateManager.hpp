#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include <unordered_map>
#include <functional>

class State;

class StateManager {
public:
    using StateFactory = std::function<std::unique_ptr<State>(sf::RenderWindow&)>;

    StateManager(unsigned int windowWidth, unsigned int windowHeight, const std::string& windowTitle);

    // Register a state factory with a name
    void registerState(const std::string& name, StateFactory factory);

    // Set which state to start with
    void setInitialState(const std::string& name);

    // Main loop - runs states until one returns empty string or "quit"
    void run();

private:
    std::unique_ptr<State> createState(const std::string& name);

    sf::RenderWindow m_window;
    std::unordered_map<std::string, StateFactory> m_stateFactories;
    std::string m_currentStateName;
};
