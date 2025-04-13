#ifndef MANAGE_STATE_HPP
#define MANAGE_STATE_HPP

#include <SFML/Graphics.hpp>

class ManageState
{
public:
    virtual ~ManageState();

    virtual bool LoadRessources(sf::RenderWindow& window) = 0;
    virtual void handleEvents(sf::RenderWindow& window, sf::Event& event) = 0;
    virtual void update() = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual void isPaused(bool pausedState) = 0;
};

#endif