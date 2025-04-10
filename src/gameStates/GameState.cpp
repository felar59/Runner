#include "GameState.hpp"
#include "LoopManagement.hpp"
#include <iostream>

GameState::GameState(){
    std::cout << "Création de l'état Game" << std::endl;
};
GameState::~GameState(){
    std::cout << "Création de l'état Game" << std::endl;
};

bool GameState::LoadRessources(sf::RenderWindow& window) {
    // Load Player
    player = Player(3, {(400.0f/1920.0f) * window.getSize().x, 0.0f});

    drawPlayer.setRadius(window.getSize().y / 25);
    drawPlayer.setFillColor(sf::Color::White);

    // start Clock
    clock.restart();

    // Load tiles
    Tiles tiles;

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
    // Move floor for runner
    sf::Int32 elapsed = clock.getElapsedTime().asSeconds();
    tiles.moves(elapsed);    

    // Gravity on player and collision
    drawPlayer.setPosition(player.getPos()[0], player.getPos()[1]);
    onFloor = player.ApplyGravity(tiles.getVector(), drawPlayer);
    if (onFloor) {
        doubleJump = true;
    }
};

void GameState::draw(sf::RenderWindow& window) {
    
    // Player
    drawPlayer.setPosition(player.getPos()[0], player.getPos()[1]);
    // Other smaller player
    sf::CircleShape dbljumpPlayer = drawPlayer;
    dbljumpPlayer.setRadius(drawPlayer.getRadius() / 1.1);
    dbljumpPlayer.setFillColor(sf::Color::White);
    dbljumpPlayer.setPosition(player.getPos()[0] + drawPlayer.getRadius() / 12, player.getPos()[1] + drawPlayer.getRadius() / 12);
    if(doubleJump){
        drawPlayer.setFillColor(sf::Color::Green);
    } else{
        drawPlayer.setFillColor(sf::Color::Red);
    }
    window.draw(drawPlayer);
    window.draw(dbljumpPlayer);
    tiles.draw(window);

};

void GameState::setLoopManager(LoopManagement* manager) {
    loopMain = manager;
}