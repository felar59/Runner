#include "Tiles.hpp"
#include <iostream>


Tiles::Tiles(){
    // Initialize the tiles
    tiles.resize(9, std::vector<Tile>(20, Tile(0, 0, 0, 0)));
    noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
    noise.SetFrequency(0.1f);
    noise.SetSeed(rand() % 500);
    
    for (int x = 0; x < 20; x++){
        for (int y = 5; y < 9; ++y) {
            tiles[y][x] = Tile(x * TileSizeX, y * TileSizeY, TileSizeX, TileSizeY);
        }
    }

}

Tiles::~Tiles(){
    tiles.clear();
};

void Tiles::draw(sf::RenderWindow& window){
    for (size_t y = 0; y < tiles.size(); y++){
        for (size_t x = 0; x < tiles[y].size(); x++){
            tiles[y][x].draw(window);
        }
    }
}

int Tiles::size(){
    return tiles.size();
}

std::vector<std::vector<Tile>>& Tiles::getVector(){
    return tiles;
}

void Tiles::shift(std::vector<std::vector<Tile>>& tiles, sf::Int32 elapsed){
    // Shift all tiles to the left
    for (size_t y = 0; y < tiles.size(); y++){
        for (size_t x = 0; x < tiles[y].size() - 1; x++){
            tiles[y][x] = tiles[y][x+1];
            tiles[y][x].setPosition(x * TileSizeX, y * TileSizeY);
        }
    }

    // Create new tiles on the last column
    noiseVariationForce += 0.01f + elapsed / 100.0f;
    std::cout << "Difficulty : " <<  0.01f + elapsed / 100.0f << std::endl;
    for (size_t y = 0; y < tiles.size(); y++){
        float n = noise.GetNoise(noiseVariationForce, 0.0f);
        int groundHeight = static_cast<int>((n + 1.0f) / 1.5f * (9-1));
    
        if (int(y) >= groundHeight) {
            tiles[y][19] = Tile(20 * TileSizeX, y * TileSizeY, TileSizeX, TileSizeY);
        } else {
            tiles[y][19] = Tile(0, 0, 0, 0);
        }
    }
}

void Tiles::moves(sf::Int32 elapsed){
    bool needShift = false;

    for (size_t y = 0; y < tiles.size(); y++){
        for (size_t x = 0; x < tiles[y].size(); x++){
            tiles[y][x].setPosition(tiles[y][x].getPos()[0] - GroundSpeed, tiles[y][x].getPos()[1]);
            // If first column is out of screen
            if (tiles[y][x].getPos()[0] < -TileSizeX)
            {
                needShift = true;
            }
        }
    }

    // Shift tiles and create a new one if we need
    if(needShift){
        shift(tiles, elapsed);
    }
}
