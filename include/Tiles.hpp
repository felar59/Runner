#ifndef Tiles_hpp
#define Tiles_hpp


#include <SFML/Graphics.hpp>
#include "Tile.hpp"
#include "FastNoiseLite.h"


class Tiles
{
private:
    std::vector<std::vector<Tile>> tiles;
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    int TileSizeX = desktopMode.width/16;
    int TileSizeY = desktopMode.height/9.2;
    int GroundSpeed = 7;
    FastNoiseLite noise;
    float noiseVariationForce = 0.0f;


public:
    Tiles();
    ~Tiles();

    // Getters
    int size();
    std::vector<std::vector<Tile>>& getVector();

    void moves(sf::Int32 elapsed);
    void draw(sf::RenderWindow& window);
    void shift(std::vector<std::vector<Tile>>& tiles, sf::Int32 elapsed);
};

#endif