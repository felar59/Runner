#include <Enemy.hpp>
#include <iostream>
#include <utility>
#include <random>
#include "Collision.hpp"

Enemy::Enemy() : pos({-300.f, 500.f}), enemyHabit("Idler") { 
}

Enemy::Enemy(sf::Vector2f beginPos, std::string habit) {
    pos = beginPos;
    enemyHabit = habit;
};

Enemy::~Enemy() {
}

// Getter
sf::Vector2f Enemy::getPos() {
    return pos;
}

// Setter
void Enemy::setPos(sf::Vector2f newPos) {
    pos = newPos;
}

// Others
void Enemy::LoadEnemy(sf::RenderWindow& window){
    const int sizeCatTiles = 32;
    const float scale = (window.getSize().x / 16.f) / sizeCatTiles; // Scale for enemy with tile size
    const std::vector<std::pair<int, std::string>> tileSetPath = 
        {{8, "Idle"},
         {8, "Born"}, 
         {8, "Sleep"},
         {13, "Jump"},
         {4, "Walk"},
         {15, "Death"}};

    // Load the textures and create the sprites
    for (size_t i = 0; i < tileSetPath.size(); i++) {
        sf::Image currentTileset;
        if (!currentTileset.loadFromFile("assets/Enemy/" + tileSetPath[i].second + ".png")) {
            std::cerr << "Error loading " + tileSetPath[i].second + ".png" << std::endl;
        }
        AnimationType currentType = static_cast<AnimationType>(i);
        animations[currentType].speed = 0.8f / tileSetPath[i].first; // Proportion for 0.1f for 8 frames
        animations[currentType].textures.resize(tileSetPath[i].first);
        animations[currentType].sprites.resize(tileSetPath[i].first);
        // Apply the texture to the sprite
        for (int j = 0; j < tileSetPath[i].first; j++) {
            sf::Texture tempTexture;
            if (!tempTexture.loadFromImage(currentTileset, sf::IntRect(j*sizeCatTiles, 0, sizeCatTiles, sizeCatTiles))){
                std::cerr << "Erreur chargement texture frame " << j << std::endl;
            }
            animations[currentType].textures[j] = tempTexture;
            sf::Sprite tempSprite;
            tempSprite.setTexture(animations[currentType].textures[j]);
            tempSprite.setScale(-scale, scale);
            animations[currentType].sprites[j] = tempSprite;
        }
    }
    currentSkin = animations[AnimationType::IDLE].sprites[0];
    hitboxEnemy = sf::RectangleShape(sf::Vector2f(sizeCatTiles * scale, sizeCatTiles*scale)); // (window.getSize().y / 9)/16 to fit with the texture and get ur feet in the ground
    hitboxEnemy.setOutlineColor(sf::Color::Red);
    hitboxEnemy.setFillColor(sf::Color::Transparent);
    hitboxEnemy.setOutlineThickness(1.0f);
    hitboxEnemy.setPosition(pos.x, pos.y);
}

void Enemy::ApplyGravity(std::vector<std::vector <Tile>>& tiles, float GroundSpeed, float deltaTime){
    if (pos.x > -hitboxEnemy.getGlobalBounds().width*2) {
            pos.x -= GroundSpeed * deltaTime;
            if (enemyHabit == "Walker" || enemyHabit == "Jumper") {
                Velocity += gravity * deltaTime;
                pos.y += Velocity * deltaTime;
                if (enemyHabit == "Walker") {
                    pos.x -= GroundSpeed * deltaTime / 2;
                }
            }
            
            hitboxEnemy.setPosition(pos.x, pos.y);
            
            if (enemyHabit != "Walker"){
                if (pos.y > floorLimit) {
                    Velocity = 0;
                    pos.y = floorLimit;
                }
            } else {
                for (size_t y = 0; y < tiles.size(); y++){
                    for (size_t x = 0; x < tiles[y].size(); x++){
                        if (tiles[y][x].getRect().getSize().x == 0 || tiles[y][x].getRect().getSize().y == 0) continue;
                        
                        sf::RectangleShape tileShape = tiles[y][x].getRect();
                        if(RectRectCollision(hitboxEnemy, tileShape)){
                            Velocity = 0;
                            pos.y = tileShape.getPosition().y - hitboxEnemy.getGlobalBounds().height;
                            hitboxEnemy.setPosition(pos.x, pos.y); 
                        }
                    } 
                }
            }
        }
    }

void Enemy::changeSkin(AnimationType type, float deltaTime) {
    animations[type].elapsedTime += deltaTime;
    if (animations[type].elapsedTime >= animations[type].speed) {
        animations[type].currentFrame = (animations[type].currentFrame + 1) % animations[type].textures.size();
        currentSkin.setTexture(animations[type].textures[animations[type].currentFrame]);
        animations[type].elapsedTime = 0.f;
    }
}

void Enemy::updateSkin(float deltaTime) {
    if(pos.x < 1920.f && HasBorn == false) {
        lastHabit = enemyHabit;
        changeSkin(AnimationType::BORN, deltaTime);
        if (animations[AnimationType::BORN].currentFrame == static_cast<int>(animations[AnimationType::BORN].textures.size()) - 1) {
            animations[AnimationType::BORN].currentFrame = 0;
            enemyHabit = lastHabit;
            HasBorn = true;
        }
    } else{
        if (enemyHabit == "Idler") {
            changeSkin(AnimationType::IDLE, deltaTime);
        } else if (enemyHabit == "Sleeper") {
            changeSkin(AnimationType::SLEEP, deltaTime);
        } else if (enemyHabit == "Jumper") {
            changeSkin(AnimationType::JUMP, deltaTime);
            if (animations[AnimationType::JUMP].currentFrame == 0 && Velocity == 0) {
                Velocity = -16.f/0.016f;
            }
        } else if (enemyHabit == "Walker"){
            changeSkin(AnimationType::WALK, deltaTime);
        }
    }
    currentSkin.setPosition(pos.x + hitboxEnemy.getGlobalBounds().width, pos.y);
    hitboxEnemy.setPosition(pos.x, pos.y);
}

void Enemy::draw(sf::RenderWindow& window){
    window.draw(currentSkin);
    // window.draw(hitboxEnemy);
}

void Enemy::summonEnemy(sf::Vector2f summoningPos, float habitFactor){
    if(pos.x < -hitboxEnemy.getGlobalBounds().width*2) {
        if (rand() % 100 < habitFactor*10 + 10) {
            sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
            // desktopMode.height / 9.f / 16.f is the 1/16th of a tile to get the feet on the ground
            pos = {summoningPos.x, summoningPos.y + (desktopMode.height / 9.f / 16.f)};
            // Chance of summoning stronger ennemy based on habitFactor
            // naming pour une variable genre tempsconséquance:
            size_t timeConsecuence = static_cast<size_t>(habitFactor * 3);
            if (timeConsecuence > 2){
                timeConsecuence = 2;
            }
            size_t index = timeConsecuence + (rand() % 2) % (possibleHabits.size());
            enemyHabit = possibleHabits[index];

            if (enemyHabit != "Walker") {
                floorLimit = pos.y + (desktopMode.height / 9.f / 16.f);
            }
            HasBorn = false;
        }
    }
}