#include "Tile.hpp"
#include <random>

Tile::Tile() : x(0), y(0), width(0), height(0) {
}

Tile::Tile(int x, int y, int width, int height) : x(x), y(y), width(width), height(height) {
    shape.setSize(sf::Vector2f(width, height));
    shape.setPosition(x, y);
    shape.setFillColor(sf::Color::White);
}

Tile::~Tile() {
}

// Setters
void Tile::setPosition(int x, int y){
    this->x = x;
    this->y = y;
    shape.setPosition(static_cast<float>(x), static_cast<float>(y));
};
void Tile::setSize(int width, int height){
    this->width = width;
    this->height = height;
    shape.setSize(sf::Vector2f(static_cast<float>(width), static_cast<float>(height)));
};

// Getters
sf::RectangleShape Tile::getRect(){
    return shape;
};

std::vector<int> Tile::getPos(){
    return {x, y};
}

void Tile::draw(sf::RenderWindow& window){
    window.draw(shape);
};