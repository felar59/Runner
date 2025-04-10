#ifndef PAUSE_MENU_HPP
#define PAUSE_MENU_HPP

#include <SFML/Graphics.hpp>
#include "ManageState.hpp"
#include "LoopManagement.hpp"
#include "MenuState.hpp"

class LoopManagement;

class PauseMenu
{
private:
    sf::Font font;
    sf::Text resumeButtonText;
    sf::Text menuButtonText;
    sf::Text exitButtonText;
    sf::RectangleShape resumeButton;
    sf::RectangleShape menuButton;
    sf::RectangleShape exitButton;
    sf::RectangleShape lowOpacityBg;
    sf::RectangleShape blackButtonBehind;

    LoopManagement* loopMain = nullptr;

public:
    PauseMenu();
    ~PauseMenu();

    void LoadRessources(sf::RenderWindow& window);
    void drawPause(sf::RenderWindow& window);
    void handleEvents(sf::RenderWindow& window, sf::Event& event, bool& inPause);

    void setLoopManager(LoopManagement* manager);
};

#endif