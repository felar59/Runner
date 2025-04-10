#ifndef LOOP_MANAGEMENT_HPP
#define LOOP_MANAGEMENT_HPP

#include <SFML/Graphics.hpp>
#include <memory>
#include "PauseMenu.hpp"
#include "ManageState.hpp"

class PauseMenu;

class LoopManagement
{
private:
    std::unique_ptr<ManageState>  currentState;
    sf::RenderWindow* window;
    PauseMenu* pause;
    bool inPause = false;

public:
    LoopManagement();
    ~LoopManagement();

    void run(sf::RenderWindow& window);
    void changeState(std::unique_ptr<ManageState> newState, sf::RenderWindow& window);
};

#endif