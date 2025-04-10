#include "MenuState.hpp"
#include "GameState.hpp"
#include "LoopManagement.hpp"
#include <iostream>

MenuState::MenuState(){
    std::cout << "Création de l'état Menu" << std::endl;
};
MenuState::~MenuState(){
    std::cout << "Déstruction de l'état Menu" << std::endl;

};

bool MenuState::LoadRessources(sf::RenderWindow& window) {
    if (!font.loadFromFile("assets/fonts/pixelFont.ttf")) {
        std::cerr << "Error loading font" << std::endl;
        return false;
    }
    sf::Vector2u windowSize = window.getSize();

    playButton.setSize(sf::Vector2f(windowSize.x / 4, windowSize.y / 8));
    playButton.setFillColor(sf::Color::White);
    playButton.setPosition(windowSize.x/2 - playButton.getSize().x/2, windowSize.y/2 - playButton.getSize().y);

    exitButton.setSize(sf::Vector2f(windowSize.x / 4, windowSize.y / 8));
    exitButton.setFillColor(sf::Color::White);
    exitButton.setPosition(windowSize.x/2 - playButton.getSize().x/2, windowSize.y/2 + 5);

    playButtonText.setFont(font);
    playButtonText.setString("Play");
    playButtonText.setCharacterSize(65);
    playButtonText.setFillColor(sf::Color::Black);
    playButtonText.setPosition(playButton.getPosition().x + playButton.getSize().x / 2 - playButtonText.getGlobalBounds().width / 2,
                                playButton.getPosition().y + playButton.getSize().y / 2 - playButtonText.getGlobalBounds().height);

    exitButtonText.setFont(font);
    exitButtonText.setString("Exit");
    exitButtonText.setCharacterSize(65);
    exitButtonText.setFillColor(sf::Color::Black);
    exitButtonText.setPosition(exitButton.getPosition().x + exitButton.getSize().x / 2 - exitButtonText.getGlobalBounds().width / 2,
                                exitButton.getPosition().y + exitButton.getSize().y / 2 - exitButtonText.getGlobalBounds().height);

    return true;
};

void MenuState::handleEvents(sf::RenderWindow& window, sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed){
        if (event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            if (playButton.getGlobalBounds().contains(mousePos)) {
                std::cout << "Play button clicked" << std::endl;
                std::unique_ptr<GameState> gameState = std::make_unique<GameState>();
                gameState->setLoopManager(loopMain);
                loopMain->changeState(std::move(gameState), window);
            }
            else if (exitButton.getGlobalBounds().contains(mousePos)) {
                std::cout << "Exit button clicked" << std::endl;
                window.close();
            }
        }
    }
};
void MenuState::update() {
    // Update menu logic here
};
void MenuState::draw(sf::RenderWindow& window) {
    
    window.draw(playButton);
    window.draw(exitButton);
    window.draw(playButtonText);
    window.draw(exitButtonText);

};

void MenuState::setLoopManager(LoopManagement* manager) {
    loopMain = manager;
}