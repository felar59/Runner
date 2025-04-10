#include "Player.hpp"
#include <iostream>

Player::Player() : health(3), pos({0.0f, 0.0f}) {
    // Valeurs par défaut
}

Player::Player(int hp, std::vector<float> beginPos){
    health = hp;
    pos = beginPos;
};

Player::~Player(){
};

// Getter
std::vector<float> Player::getPos(){
    return pos;
};
int Player::getHeatlh(){
    return health;
};

// Setter
void Player::setPos(std::vector<float> newPos){
    pos = newPos;
};
void Player::setHealth(int newHealth){
    health = newHealth;
};

// Autres
bool circleRectCollision(sf::CircleShape& circle, sf::RectangleShape& rect) {
    sf::Vector2f circleCenter = circle.getPosition() + sf::Vector2f(circle.getRadius(), circle.getRadius());
    sf::FloatRect rectBounds = rect.getGlobalBounds();

    float closestX = std::clamp(circleCenter.x, rectBounds.left, rectBounds.left + rectBounds.width);
    float closestY = std::clamp(circleCenter.y, rectBounds.top, rectBounds.top + rectBounds.height);

    float dx = circleCenter.x - closestX;
    float dy = circleCenter.y - closestY;

    return (dx * dx + dy * dy) < (circle.getRadius() * circle.getRadius());
}

bool Player::ApplyGravity(std::vector<std::vector <Tile>>& tiles, sf::CircleShape& drawPlayer){
    SpeedY += gravity * deltaTime;
    pos[1] += SpeedY;

    drawPlayer.setPosition(pos[0], pos[1]);

    for (size_t y = 0; y < tiles.size(); y++){
        for (size_t x = 0; x < tiles[y].size(); x++){
            if (tiles[y][x].getRect().getSize().x == 0 || tiles[y][x].getRect().getSize().y == 0) continue;

            sf::RectangleShape tileShape = tiles[y][x].getRect();
            if(circleRectCollision(drawPlayer, tileShape)){
                SpeedY = 0;
                pos[1] = tileShape.getPosition().y - drawPlayer.getRadius() * 2;
                drawPlayer.setPosition(pos[0], pos[1]); 
                return true;
            }
        }
    }
    return false;
}


bool Player::jump(bool doubleJump, bool onFloor){
    SpeedY = -16;
    if(!doubleJump){
        return true;
    } else if (!onFloor)
    {
        return false;
    }
    return true;
}

