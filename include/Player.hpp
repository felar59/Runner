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
    sf::Vector2f pos;
    float Velocity = 0.0f;
    float gravity = 60.0f/0.016f;
    sf::RectangleShape hitboxPlayer;
    std::vector<sf::Texture> runTextures;
    std::vector<sf::Sprite> runSprites;
    std::vector<sf::Texture> jumpTextures;
    std::vector<sf::Sprite> jumpSprites;
    
    sf::Sprite currentSkin;


public:
    Player(); 
    Player(int health, sf::Vector2f pos);
    ~Player();
    // Getter
    sf::Vector2f getPos();
    int getHeatlh();

    // Setter
    void setPos(sf::Vector2f newPos);
    void setHealth(int newHealth);

    // Others
    void LoadPlayer(sf::RenderWindow& window);
    bool ApplyGravity(std::vector<std::vector <Tile>>& tiles, float deltaTime);
    bool jump(bool doubleJump, bool onFloor);
    void draw(sf::RenderWindow& window);
    void updateSkin(float deltaTime);
};

#endif