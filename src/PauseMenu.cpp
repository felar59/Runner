#include "PauseMenu.hpp"
#include <iostream>

PauseMenu::PauseMenu(){
}
PauseMenu::~PauseMenu(){
}

void PauseMenu::LoadRessources(sf::RenderWindow& window){
    if (!font.loadFromFile("assets/fonts/pixelFont.ttf")) {
        std::cerr << "Error loading font" << std::endl;
    }
    resumeButtonText.setString("Resume");
    menuButtonText.setString("Menu");
    exitButtonText.setString("Exit");
    resumeButtonText.setFont(font);
    menuButtonText.setFont(font);
    exitButtonText.setFont(font);
    resumeButtonText.setCharacterSize(65);
    menuButtonText.setCharacterSize(65);
    exitButtonText.setCharacterSize(65);
    resumeButtonText.setFillColor(sf::Color::Black);
    menuButtonText.setFillColor(sf::Color::Black);
    exitButtonText.setFillColor(sf::Color::Black);

    lowOpacityBg.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
    lowOpacityBg.setFillColor(sf::Color(0, 0, 0, 150));
    lowOpacityBg.setPosition(0, 0);

    sf::RectangleShape blackButtonBehind;
    blackButtonBehind.setSize(sf::Vector2f(window.getSize().x / 4 + 10, window.getSize().y / 8 + 10));

    sf::Vector2u windowSize = window.getSize();
    resumeButton.setSize(sf::Vector2f(windowSize.x / 4, windowSize.y / 8));
    menuButton.setSize(sf::Vector2f(windowSize.x / 4, windowSize.y / 8));
    exitButton.setSize(sf::Vector2f(windowSize.x / 4, windowSize.y / 8));

    resumeButton.setFillColor(sf::Color::White);
    menuButton.setFillColor(sf::Color::White);
    exitButton.setFillColor(sf::Color::White);

    resumeButton.setPosition(windowSize.x/2 - resumeButton.getSize().x/2, windowSize.y/2 - resumeButton.getSize().y*1.1);
    menuButton.setPosition(windowSize.x/2 - menuButton.getSize().x/2, windowSize.y/2);
    exitButton.setPosition(windowSize.x/2 - exitButton.getSize().x/2, windowSize.y/2 + exitButton.getSize().y*1.1);

    resumeButtonText.setPosition(resumeButton.getPosition().x + resumeButton.getSize().x / 2 - resumeButtonText.getGlobalBounds().width / 2,
                                resumeButton.getPosition().y + resumeButton.getSize().y / 2 - resumeButtonText.getGlobalBounds().height);
    menuButtonText.setPosition(menuButton.getPosition().x + menuButton.getSize().x / 2 - menuButtonText.getGlobalBounds().width / 2,
                                menuButton.getPosition().y + menuButton.getSize().y / 2 - menuButtonText.getGlobalBounds().height);
    exitButtonText.setPosition(exitButton.getPosition().x + exitButton.getSize().x / 2 - exitButtonText.getGlobalBounds().width / 2,
                                exitButton.getPosition().y + exitButton.getSize().y / 2 - exitButtonText.getGlobalBounds().height);
}

void PauseMenu::drawPause(sf::RenderWindow& window){
    window.draw(lowOpacityBg);
    window.draw(resumeButton);
    window.draw(menuButton);
    window.draw(exitButton);
    window.draw(resumeButtonText);
    window.draw(menuButtonText);
    window.draw(exitButtonText);
}

void PauseMenu::handleEvents(sf::RenderWindow& window, sf::Event& event, bool& inPause){
    if (event.type == sf::Event::MouseButtonPressed){
        if (event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            if (resumeButton.getGlobalBounds().contains(mousePos)) {
                inPause = false;
            }
            else if (menuButton.getGlobalBounds().contains(mousePos)) {
                inPause = false;
                std::unique_ptr<MenuState> menu = std::make_unique<MenuState>();
                menu->setLoopManager(std::move(loopMain));
                loopMain->changeState(std::move(menu), window);
            }
            else if (exitButton.getGlobalBounds().contains(mousePos)) {
                window.close();
            }
        }
    }
}

void PauseMenu::setLoopManager(LoopManagement* manager) {
    loopMain = manager;
}