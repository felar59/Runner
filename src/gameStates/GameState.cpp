#include "GameState.hpp"
#include "LoopManagement.hpp"
#include <iostream>

GameState::GameState(sf::RenderWindow& window) : tiles(window){
    std::cout << "Création de l'état Game" << std::endl;
};
GameState::~GameState(){
    std::cout << "Création de l'état Game" << std::endl;
};

bool GameState::LoadRessources(sf::RenderWindow& window) {
    // Load Player
    player = Player(3, {(400.0f/1920.0f) * window.getSize().x, 0.0f});
    player.LoadPlayer(window);
    
    //Load Enemy
    enemy.LoadEnemy(window);

    // Load tiles
    Tiles tiles(window);
    
    // Load paralax background
    paralaxBG.LoadRessources(window);
    
    // start Clock
    clock.restart();
    lastFrameTime = clock.getElapsedTime();

    return true;
};

void GameState::handleEvents(sf::RenderWindow& window, sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Space && (onFloor || doubleJump)) {
            // Jump and allowed or not doubleJump
            doubleJump = player.jump(doubleJump, onFloor);
        }
    }
};

void GameState::update() {
    std::cout << "deltatime " << deltaTime << std::endl;
    // Set deltaTime
    sf::Time currentTime = clock.getElapsedTime();
    deltaTime = (currentTime - lastFrameTime).asSeconds();
    lastFrameTime = currentTime;

    // update paralax background
    paralaxBG.Update(deltaTime);

    // Move floor for runner
    tiles.moves(deltaTime, enemy); 
    
    
    // Gravity on player and collision
    onFloor = player.ApplyGravity(tiles.getVector(), deltaTime);
    if (onFloor) {
        doubleJump = true;
    }
    // Change Skin player depending on velocity
    player.updateSkin(deltaTime);
    
    // Gravity on enemy and collision
    enemy.ApplyGravity(tiles.getVector(), tiles.getSpeed(), deltaTime);
    
    // Change Skin enemy depending on velocity
    enemy.updateSkin(deltaTime);
};

void GameState::draw(sf::RenderWindow& window) {
    // Paralax background
    paralaxBG.Draw(window);

    // Player
    player.draw(window);

    // Enemy
    enemy.draw(window);
    
    // Tiles
    tiles.draw(window);
};

void GameState::setLoopManager(LoopManagement* manager) {
    loopMain = manager;
}

void GameState::setDeltaTime(float deltaTime) {
    this->deltaTime = deltaTime;
}