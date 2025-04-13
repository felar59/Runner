#include "Tile.hpp"
#include <iostream>
#include <random>

Tile::Tile() : x(0), y(0), width(0), height(0), Void(true) {
}

Tile::Tile(float x, float y, float width, float height, bool Void) : x(x), y(y), width(width), height(height), Void(Void) {
    shape.setSize(sf::Vector2f(width, height));
    shape.setPosition(x, y);
    shape.setFillColor(sf::Color::Black);
    this->Void = Void;
}

Tile::~Tile() {
}

// Setters
void Tile::setPosition(float x, float y){
    this->x = x;
    this->y = y;
    shape.setPosition(static_cast<float>(x), static_cast<float>(y));
};
void Tile::setSize(float width, float height){
    this->width = width;
    this->height = height;
    shape.setSize(sf::Vector2f(static_cast<float>(width), static_cast<float>(height)));
};

void Tile::setSprite(sf::Sprite& newSprite){
    sprite = newSprite;
};

void Tile::setTexture(const sf::Texture& texture) {
    sprite.setTexture(texture);
}

// Getters

sf::RectangleShape Tile::getRect(){
    shape.setPosition(x, y + (1080.f/9.f)/16.f);
    return shape;
};

sf::Vector2f Tile::getPos(){
    return {x, y};
}

bool Tile::isVoid(){
    return Void;
}

// Others
void Tile::draw(sf::RenderWindow& window){
    if (width != 0 && height != 0) {
        sprite.setPosition(x, y);
        window.draw(sprite);
    }
};