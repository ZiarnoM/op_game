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

    bool getIsMoving();
    void setIsMoving(bool value);

private:
    // initialization
    void initVariables();
    void initTextures();
    void initSprite();
    void initAnimations();

    // Movement
    void updateMovement();
    // Animations
    void updateAnimations();

    // fields
    bool isMoving;
    float speed;
    sf::Clock animationTimer;
    sf::IntRect currentFrame;
    sf::Sprite sprite;
    sf::Texture idleSheet;
};