#ifndef Tile_hpp
#define Tile_hpp


#include <SFML/Graphics.hpp>

class Tile
{
private:
    int x;
    int y;
    int width;
    int height;
    sf::RectangleShape shape;
    
public:
    Tile();
    Tile(int x, int y, int width, int height);
    ~Tile();

    // Setters
    void setPosition(int x, int y);
    void setSize(int width, int height);

    // Getters
    sf::RectangleShape getRect();
    std::vector<int> getPos();

    void draw(sf::RenderWindow& window);
};

#endif