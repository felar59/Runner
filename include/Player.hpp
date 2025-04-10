#ifndef Player_hpp
#define Player_hpp

#include <SFML/Graphics.hpp>
#include <vector>
#include "Tiles.hpp"
#include "Tile.hpp"

class Player
{
private:
    int health;
    std::vector<float> pos;
    float SpeedY = 0.0f;
    float gravity = 50.0f;
    float deltaTime = 0.016f;
    
public:
    Player(); 
    Player(int health, std::vector<float> pos);
    ~Player();
    // Getter
    std::vector<float> getPos();
    int getHeatlh();

    // Setter
    void setPos(std::vector<float> newPos);
    void setHealth(int newHealth);

    // Autres
    bool ApplyGravity(std::vector<std::vector <Tile>>& tiles, sf::CircleShape& drawPlayer);
    bool jump(bool doubleJump, bool onFloor);
};

#endif