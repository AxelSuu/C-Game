#pragma once

#include "State.hpp"
#include "../sprites/Player.hpp"
#include "../sprites/Platform.hpp"
#include "../sprites/Enemy.hpp"
#include "../sprites/Walker.hpp"
#include "../sprites/Chaser.hpp"
#include "../sprites/Jumper.hpp"
#include "../sprites/Coin.hpp"
#include "../libs/Camera.hpp"
#include "../ui/HUD.hpp"

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

class Game : public State {
public:
    explicit Game(sf::RenderWindow& window);

    std::string run() override;
    void onEnter() override;

private:
    void processEvents();
    void update(float deltaTime);
    void render();

    void createLevel();
    void spawnEnemies();
    void spawnCoins();
    void handleEnemyCollisions();
    void handleCoinCollisions();
    void removeDeadEnemies();
    void resetLevel();

    std::unique_ptr<Player> m_player;
    std::unique_ptr<Camera> m_camera;
    std::unique_ptr<HUD> m_hud;
    std::vector<Platform> m_platforms;
    std::vector<std::unique_ptr<Enemy>> m_enemies;
    std::vector<Coin> m_coins;
    int m_coinsCollected;

    sf::Clock m_clock;
    bool m_running;
    std::string m_nextState;

    // Level bounds
    static constexpr float LEVEL_WIDTH = 3000.0f;
    static constexpr float LEVEL_HEIGHT = 1000.0f;
};
