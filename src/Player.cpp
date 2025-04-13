#include "Player.hpp"
#include "Collision.hpp"
#include <iostream>

Player::Player() : health(3), pos({0.0f, 0.0f}) {
    // Valeurs par défaut
}

Player::Player(int hp, sf::Vector2f beginPos){
    health = hp;
    pos = beginPos;
};

Player::~Player(){
};

// Getter
sf::Vector2f Player::getPos(){
    return pos;
};
int Player::getHeatlh(){
    return health;
};

// Setter
void Player::setPos(sf::Vector2f newPos){
    pos = newPos;
};
void Player::setHealth(int newHealth){
    health = newHealth;
};

// Others
void Player::LoadPlayer(sf::RenderWindow& window){
    sf::Image runTileset;
    if (!runTileset.loadFromFile("assets/Player/Run.png")) {
        std::cerr << "Error loading runTileset.png" << std::endl;
    }
    const std::vector<sf::Vector2f> textureCoords = {
        {0, 0}, {21, 0}, {43, 0}, {64, 0}
    };
    const std::vector<sf::Vector2f> textureSize = {
        {20, 28}, {21, 28}, {20, 28}, {21, 28}
    };

    for (int i = 0; i < 4; i++) {
        sf::Texture tempTexture;
        if (!tempTexture.loadFromImage(runTileset, sf::IntRect(textureCoords[i].x, textureCoords[i].y, textureSize[i].x, textureSize[i].y))){
            std::cerr << "Erreur chargement texture frame " << i << std::endl;
        }
        runTextures.push_back(tempTexture);
    }
    for(auto& texture : runTextures){
        sf::Sprite tempSprite;
        tempSprite.setTexture(texture);
        float scale = window.getSize().x / 20.f / texture.getSize().x;
        tempSprite.setScale(scale, scale);
        
        runSprites.push_back(tempSprite);
    }
    sf::Image jumpTileset;
    if (!jumpTileset.loadFromFile("assets/Player/Jump.png")) {
        std::cerr << "Error loading jumpTileset.png" << std::endl;
    }
    std::vector<sf::Vector2f> jumpTextureCoords = {
        {0, 0}, {22, 0}, {45, 0}, {70, 0}
    };
    std::vector<sf::Vector2f> jumpTextureSize = {
        {22, 29}, {22, 29}, {24, 29}, {24, 29}
    };
    for (int i = 0; i < 5; i++) {
        sf::Texture tempTexture;
        if (!tempTexture.loadFromImage(jumpTileset, sf::IntRect(jumpTextureCoords[i].x, jumpTextureCoords[i].y, jumpTextureSize[i].x, jumpTextureSize[i].y))){
            std::cerr << "Erreur chargement texture frame " << i << std::endl;
        }
        jumpTextures.push_back(tempTexture);
    }
    for(auto& texture : jumpTextures){
        sf::Sprite tempSprite;
        tempSprite.setTexture(texture);
        float scale = window.getSize().x / 20.f / texture.getSize().x;
        tempSprite.setScale(scale, scale);        
        jumpSprites.push_back(tempSprite);
    }

    hitboxPlayer = sf::RectangleShape(sf::Vector2f(runSprites[0].getGlobalBounds().width, runSprites[0].getGlobalBounds().height - ((window.getSize().y / 9)/16))); // (window.getSize().y / 9)/16 to fit with the texture and get ur feet in the ground
    hitboxPlayer.setFillColor(sf::Color::Transparent);
    hitboxPlayer.setOutlineColor(sf::Color::Red);
    hitboxPlayer.setOutlineThickness(1.0f);
}

bool Player::ApplyGravity(std::vector<std::vector <Tile>>& tiles, float deltaTime){
    Velocity += gravity * deltaTime;
    pos.y += Velocity * deltaTime;

    hitboxPlayer.setPosition(pos.x, pos.y);

    for (size_t y = 0; y < tiles.size(); y++){
        for (size_t x = 3; x < 5; x++){ // Block around the player
            if (tiles[y][x].getRect().getSize().x == 0 || tiles[y][x].getRect().getSize().y == 0) continue;

            sf::RectangleShape tileShape = tiles[y][x].getRect();
            if(RectRectCollision(hitboxPlayer, tileShape)){
                Velocity = 0;
                pos.y = tileShape.getPosition().y - hitboxPlayer.getGlobalBounds().height + 2.f; // +2 for issue with windows to be sure of being on the tile and not slightly over which make us fall in a while.
                hitboxPlayer.setPosition(pos.x, pos.y); 
                return true;
            }
        } 
    }
    return false;
}


bool Player::jump(bool doubleJump, bool onFloor){
    Velocity = -17.f/0.016f;
    if(!doubleJump){
        return true;
    } else if (!onFloor)
    {
        return false;
    }
    return true;
}
 
void Player::draw(sf::RenderWindow& window){
    window.draw(currentSkin);
    window.draw(hitboxPlayer);
}

void Player::updateSkin(float deltaTime){
    static float elapsedTime = 0.0f;
    static size_t currentFrame = 0;
    std::cout << "Velocity: " << Velocity << std::endl;
    elapsedTime += deltaTime;
    if (Velocity < -10/0.016f){
        currentSkin.setTexture(jumpTextures[0], true);
        currentSkin.setScale(jumpSprites[0].getScale());
    } else if (Velocity < -4/0.016f) {
        currentSkin.setTexture(jumpTextures[1], true);
        currentSkin.setScale(jumpSprites[1].getScale());
    } else if (Velocity < 6/0.016f && Velocity != 0) {
        currentSkin.setTexture(jumpTextures[2], true);
        currentSkin.setScale(jumpSprites[2].getScale());
    } else if (Velocity > 6/0.016f) {
        currentSkin.setTexture(jumpTextures[3], true);
        currentSkin.setScale(jumpSprites[3].getScale());
    } else if (Velocity > 0 && elapsedTime <= 0.2f) {
        currentSkin.setTexture(runTextures[currentFrame], true);
        currentSkin.setScale(runSprites[currentFrame].getScale());
    } else if (Velocity == 0 && elapsedTime >= 0.2f) {
        currentFrame = (currentFrame + 1) % runTextures.size();
        currentSkin.setTexture(runTextures[currentFrame], true);
        currentSkin.setScale(runSprites[currentFrame].getScale());
        elapsedTime = 0.0f;
    }
    currentSkin.setPosition(pos.x, pos.y);
}