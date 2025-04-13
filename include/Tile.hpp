#ifndef Tile_hpp
#define Tile_hpp


#include <SFML/Graphics.hpp>

class Tile
{
private:
    float x;
    float y;
    float width;
    float height;
    bool Void;
    sf::RectangleShape shape;
    sf::Texture texture;
    sf::Sprite sprite;

    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    int TileSizeYadjust = desktopMode.height/9.f/16.f;
    
public:
    Tile();
    Tile(float x, float y, float width, float height, bool Void);
    ~Tile();

    // Setters
    void setPosition(float x, float y);
    void setSize(float width, float height);
    void setSprite(sf::Sprite& newSprite);
    void setTexture(const sf::Texture& texture);

    // Getters
    sf::RectangleShape getRect();
    sf::Vector2f getPos();
    bool isVoid();

    // Others
    void draw(sf::RenderWindow& window);
};

#endif