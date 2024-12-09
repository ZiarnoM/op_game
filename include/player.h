#pragma once
#include <SFML/Graphics.hpp>

class Player
{
public:
    Player();
    virtual ~Player();

    // general methods
    void update();
    void render(sf::RenderTarget &target);

    // getters and setters
    float getSpeed();
    void setSpeed(float value);

private:
    // initialization
    void initTextures();
    void initSprite();

    // updates
    void updateMovement();

    // fields
    float speed;
    sf::Sprite sprite;
    sf::Texture idleSheet;
};