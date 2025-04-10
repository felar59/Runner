#ifndef GameState_hpp
#define GameState_hpp

#include <SFML/Graphics.hpp>
#include "ManageState.hpp"
#include "LoopManagement.hpp"
#include "Player.hpp"
#include "Tiles.hpp"

class LoopManagement;

class GameState : public ManageState
{
private:
    LoopManagement* loopMain = nullptr;
    Player player;
    sf::CircleShape drawPlayer;
    Tiles tiles;
    bool onFloor = false;
    bool doubleJump = false;
    sf::Clock clock;
    
public:
    GameState();
    ~GameState();

    bool LoadRessources(sf::RenderWindow& window);
    void handleEvents(sf::RenderWindow& window, sf::Event& event) override;
    void update() override;
    void draw(sf::RenderWindow& window) override;
    void setLoopManager(LoopManagement* manager);
};

#endif