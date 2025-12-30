#include "Game.hpp"
#include "../core/ScoreManager.hpp"
#include <algorithm>

Game::Game(sf::RenderWindow& window)
    : State(window)
    , m_running(true)
    , m_coinsCollected(0)
{
    // Create camera
    sf::Vector2u windowSize = m_window.getSize();
    m_camera = std::make_unique<Camera>(sf::Vector2f(static_cast<float>(windowSize.x), 
                                                      static_cast<float>(windowSize.y)));
    m_camera->setSmoothness(5.0f);
    m_camera->setDeadzone({50.0f, 30.0f});
    m_camera->setBounds({{0.0f, 0.0f}, {LEVEL_WIDTH, LEVEL_HEIGHT}});
    m_camera->setUseBounds(true);

    // Create HUD
    m_hud = std::make_unique<HUD>(m_window, "../src/font/Outfit-Regular.ttf");

    // Create level and player
    createLevel();
}

void Game::onEnter()
{
    resetLevel();
}

void Game::resetLevel()
{
    // Reset score and combo
    ScoreManager::getInstance().reset();
    ScoreManager::getInstance().resetCombo();

    // Clear existing entities
    m_platforms.clear();
    m_enemies.clear();
    m_coins.clear();
    m_coinsCollected = 0;

    // Recreate level
    createLevel();
}

void Game::createLevel()
{
    // Ground platform
    m_platforms.emplace_back(sf::Vector2f(0.0f, 600.0f), sf::Vector2f(3000.0f, 50.0f), sf::Color(80, 60, 40));

    // Floating platforms - create a platformer-style level
    m_platforms.emplace_back(sf::Vector2f(200.0f, 500.0f), sf::Vector2f(150.0f, 20.0f), sf::Color(100, 80, 60));
    m_platforms.emplace_back(sf::Vector2f(400.0f, 420.0f), sf::Vector2f(150.0f, 20.0f), sf::Color(100, 80, 60));
    m_platforms.emplace_back(sf::Vector2f(600.0f, 340.0f), sf::Vector2f(150.0f, 20.0f), sf::Color(100, 80, 60));
    m_platforms.emplace_back(sf::Vector2f(850.0f, 400.0f), sf::Vector2f(200.0f, 20.0f), sf::Color(100, 80, 60));
    m_platforms.emplace_back(sf::Vector2f(1100.0f, 320.0f), sf::Vector2f(150.0f, 20.0f), sf::Color(100, 80, 60));
    m_platforms.emplace_back(sf::Vector2f(1300.0f, 450.0f), sf::Vector2f(180.0f, 20.0f), sf::Color(100, 80, 60));
    m_platforms.emplace_back(sf::Vector2f(1550.0f, 380.0f), sf::Vector2f(120.0f, 20.0f), sf::Color(100, 80, 60));
    m_platforms.emplace_back(sf::Vector2f(1750.0f, 300.0f), sf::Vector2f(200.0f, 20.0f), sf::Color(100, 80, 60));
    m_platforms.emplace_back(sf::Vector2f(2000.0f, 400.0f), sf::Vector2f(150.0f, 20.0f), sf::Color(100, 80, 60));
    m_platforms.emplace_back(sf::Vector2f(2200.0f, 500.0f), sf::Vector2f(180.0f, 20.0f), sf::Color(100, 80, 60));
    m_platforms.emplace_back(sf::Vector2f(2450.0f, 420.0f), sf::Vector2f(150.0f, 20.0f), sf::Color(100, 80, 60));
    m_platforms.emplace_back(sf::Vector2f(2650.0f, 340.0f), sf::Vector2f(200.0f, 20.0f), sf::Color(100, 80, 60));

    // Walls on sides
    m_platforms.emplace_back(sf::Vector2f(-50.0f, 0.0f), sf::Vector2f(50.0f, LEVEL_HEIGHT), sf::Color(60, 60, 60));
    m_platforms.emplace_back(sf::Vector2f(LEVEL_WIDTH, 0.0f), sf::Vector2f(50.0f, LEVEL_HEIGHT), sf::Color(60, 60, 60));

    // Create player at starting position
    m_player = std::make_unique<Player>(sf::Vector2f(100.0f, 500.0f));

    // Spawn enemies and coins
    spawnEnemies();
    spawnCoins();
}

void Game::spawnEnemies()
{
    // Walkers on ground
    m_enemies.push_back(std::make_unique<Walker>(sf::Vector2f(400.0f, 560.0f)));
    m_enemies.push_back(std::make_unique<Walker>(sf::Vector2f(800.0f, 560.0f)));
    m_enemies.push_back(std::make_unique<Walker>(sf::Vector2f(1500.0f, 560.0f)));
    m_enemies.push_back(std::make_unique<Walker>(sf::Vector2f(2300.0f, 560.0f)));

    // Jumpers on platforms
    m_enemies.push_back(std::make_unique<Jumper>(sf::Vector2f(620.0f, 300.0f)));
    m_enemies.push_back(std::make_unique<Jumper>(sf::Vector2f(1770.0f, 260.0f)));

    // Chasers
    auto chaser1 = std::make_unique<Chaser>(sf::Vector2f(1100.0f, 560.0f));
    chaser1->setTarget(m_player.get());
    m_enemies.push_back(std::move(chaser1));

    auto chaser2 = std::make_unique<Chaser>(sf::Vector2f(2000.0f, 560.0f));
    chaser2->setTarget(m_player.get());
    m_enemies.push_back(std::move(chaser2));
}

void Game::spawnCoins()
{
    // Coins on platforms (placed above each floating platform)
    m_coins.emplace_back(sf::Vector2f(275.0f, 470.0f));   // Platform at 200
    m_coins.emplace_back(sf::Vector2f(475.0f, 390.0f));   // Platform at 400
    m_coins.emplace_back(sf::Vector2f(675.0f, 310.0f));   // Platform at 600
    m_coins.emplace_back(sf::Vector2f(950.0f, 370.0f));   // Platform at 850
    m_coins.emplace_back(sf::Vector2f(1175.0f, 290.0f));  // Platform at 1100
    m_coins.emplace_back(sf::Vector2f(1390.0f, 420.0f));  // Platform at 1300
    m_coins.emplace_back(sf::Vector2f(1610.0f, 350.0f));  // Platform at 1550
    m_coins.emplace_back(sf::Vector2f(1850.0f, 270.0f));  // Platform at 1750
    m_coins.emplace_back(sf::Vector2f(2075.0f, 370.0f));  // Platform at 2000
    m_coins.emplace_back(sf::Vector2f(2290.0f, 470.0f));  // Platform at 2200
    m_coins.emplace_back(sf::Vector2f(2525.0f, 390.0f));  // Platform at 2450
    m_coins.emplace_back(sf::Vector2f(2750.0f, 310.0f));  // Platform at 2650

    // Bonus coins in harder to reach spots
    m_coins.emplace_back(sf::Vector2f(700.0f, 250.0f), 25);   // High jump coin
    m_coins.emplace_back(sf::Vector2f(1850.0f, 200.0f), 25);  // High jump coin
    m_coins.emplace_back(sf::Vector2f(2750.0f, 250.0f), 50);  // End of level bonus
}

void Game::handleCoinCollisions()
{
    sf::FloatRect playerBounds = m_player->getBounds();

    for (auto& coin : m_coins) {
        if (coin.isCollected()) continue;

        if (playerBounds.findIntersection(coin.getBounds())) {
            coin.collect();
            m_coinsCollected++;
            ScoreManager::getInstance().addScore(coin.getValue());
        }
    }
}

std::string Game::run()
{
    m_running = true;
    m_nextState = "";

    while (m_window.isOpen() && m_running) {
        float deltaTime = m_clock.restart().asSeconds();

        // Cap delta time to prevent physics issues
        if (deltaTime > 0.1f) {
            deltaTime = 0.1f;
        }

        processEvents();
        update(deltaTime);
        render();
    }

    // Return next state or quit
    if (!m_window.isOpen()) {
        return "quit";
    }
    return m_nextState;
}

void Game::processEvents()
{
    while (const std::optional event = m_window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            m_window.close();
        }

        if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            if (keyPressed->code == sf::Keyboard::Key::Escape) {
                m_nextState = "pause";
                m_running = false;
            }
        }
    }
}

void Game::update(float deltaTime)
{
    // Check if player is dead
    if (m_player->getHealth().isDead()) {
        m_nextState = "gameover";
        m_running = false;
        return;
    }

    // Handle player input
    m_player->handleInput();

    // Update player physics and collisions
    m_player->update(deltaTime, m_platforms);

    // Update enemies
    for (auto& enemy : m_enemies) {
        enemy->update(deltaTime, m_platforms);
    }

    // Handle player-enemy collisions
    handleEnemyCollisions();

    // Handle coin collection
    handleCoinCollisions();

    // Update coin animations
    for (auto& coin : m_coins) {
        coin.update(deltaTime);
    }

    // Remove dead enemies
    removeDeadEnemies();

    // Update camera to follow player
    m_camera->setTarget(m_player->getCenter());
    m_camera->update(deltaTime);

    // Update HUD
    m_hud->update(*m_player, m_coinsCollected);
}

void Game::handleEnemyCollisions()
{
    sf::FloatRect playerBounds = m_player->getBounds();

    for (auto& enemy : m_enemies) {
        if (enemy->isDead()) continue;

        sf::FloatRect enemyBounds = enemy->getBounds();
        auto intersection = playerBounds.findIntersection(enemyBounds);

        if (!intersection) continue;

        // Check if player is stomping (coming from above)
        float playerBottom = playerBounds.position.y + playerBounds.size.y;
        float enemyTop = enemyBounds.position.y;
        float playerCenterX = playerBounds.position.x + playerBounds.size.x / 2.0f;
        float enemyLeft = enemyBounds.position.x;
        float enemyRight = enemyBounds.position.x + enemyBounds.size.x;

        // Stomp detection: player falling, hitting top half of enemy
        if (playerBottom < enemyTop + enemyBounds.size.y * 0.5f &&
            playerCenterX > enemyLeft && playerCenterX < enemyRight) {
            // Stomp the enemy
            enemy->onStomped(*m_player);
        } else {
            // Enemy damages player
            enemy->onPlayerCollision(*m_player);
        }
    }
}

void Game::removeDeadEnemies()
{
    m_enemies.erase(
        std::remove_if(m_enemies.begin(), m_enemies.end(),
            [](const std::unique_ptr<Enemy>& enemy) {
                return enemy->isDead();
            }),
        m_enemies.end()
    );
}

void Game::render()
{
    m_window.clear(sf::Color(30, 30, 50));

    // Apply camera view
    m_camera->apply(m_window);

    // Draw platforms
    for (const auto& platform : m_platforms) {
        platform.draw(m_window);
    }

    // Draw coins
    for (const auto& coin : m_coins) {
        coin.draw(m_window);
    }

    // Draw enemies
    for (const auto& enemy : m_enemies) {
        enemy->draw(m_window);
    }

    // Draw player
    m_player->draw(m_window);

    // Draw HUD (on top of everything)
    m_hud->draw();

    m_window.display();
}
