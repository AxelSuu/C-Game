#include "StateManager.hpp"
#include "State.hpp"
#include <stdexcept>

StateManager::StateManager(unsigned int windowWidth, unsigned int windowHeight, const std::string& windowTitle)
    : m_window(sf::VideoMode({windowWidth, windowHeight}), windowTitle)
{
    m_window.setFramerateLimit(144);

    // Center window on screen
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    int posX = static_cast<int>(desktop.size.x - windowWidth) / 2;
    int posY = static_cast<int>(desktop.size.y - windowHeight) / 2;
    m_window.setPosition({posX, posY});
}

void StateManager::registerState(const std::string& name, StateFactory factory)
{
    m_stateFactories[name] = std::move(factory);
}

void StateManager::setInitialState(const std::string& name)
{
    m_currentStateName = name;
}

void StateManager::run()
{
    while (m_window.isOpen() && !m_currentStateName.empty() && m_currentStateName != "quit") {
        auto state = createState(m_currentStateName);
        if (!state) {
            throw std::runtime_error("Failed to create state: " + m_currentStateName);
        }

        state->onEnter();
        std::string nextState = state->run();
        state->onExit();

        m_currentStateName = nextState;
    }
}

std::unique_ptr<State> StateManager::createState(const std::string& name)
{
    auto it = m_stateFactories.find(name);
    if (it == m_stateFactories.end()) {
        return nullptr;
    }
    return it->second(m_window);
}
