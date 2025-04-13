#ifndef MenuState_hpp
#define MenuState_hpp

#include <SFML/Graphics.hpp>
#include "ManageState.hpp"
#include "LoopManagement.hpp"

class LoopManagement;

class MenuState : public ManageState
{
private:
    sf::Font font;
    sf::RectangleShape playButton;
    sf::RectangleShape exitButton;
    sf::Text playButtonText;
    sf::Text exitButtonText;
    LoopManagement* loopMain = nullptr;
    float deltaTime = 0.0f;
    sf::Clock clock;
    sf::Time lastFrameTime;
    bool isPause = false;
    
public:
    MenuState();
    ~MenuState();

    bool LoadRessources(sf::RenderWindow& window);
    void handleEvents(sf::RenderWindow& window, sf::Event& event) override;
    void update() override;
    void draw(sf::RenderWindow& window) override;
    void setLoopManager(LoopManagement* manager);
    void isPaused(bool pausedState) override;

};

#endif