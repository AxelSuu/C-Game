#include "states/StateManager.hpp"
#include "states/MenuState.hpp"
#include "states/Game.hpp"
#include "states/PauseState.hpp"
#include "states/GameOverState.hpp"

int main()
{
    StateManager stateManager(1280, 720, "Platformer Game");

    // Register all game states
    stateManager.registerState("menu", [](sf::RenderWindow& window) {
        return std::make_unique<MenuState>(window);
    });

    stateManager.registerState("game", [](sf::RenderWindow& window) {
        return std::make_unique<Game>(window);
    });

    stateManager.registerState("pause", [](sf::RenderWindow& window) {
        return std::make_unique<PauseState>(window);
    });

    stateManager.registerState("gameover", [](sf::RenderWindow& window) {
        return std::make_unique<GameOverState>(window);
    });

    // Start with the menu state
    stateManager.setInitialState("menu");

    // Run the state machine
    stateManager.run();

    return 0;
}
