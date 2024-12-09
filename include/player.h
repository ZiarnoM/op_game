#pragma once
#include <SFML/Graphics.hpp>

enum MovementState
{
    Idle,
    RunLeft,
    RunRight,
    Jump,
    Fall
};

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

    bool getMovementState();
    void setMovementState(MovementState value);

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
    MovementState state;
    float speed;
    sf::Clock animationTimer;
    sf::IntRect currentFrame;
    sf::Sprite sprite;
    sf::Texture idleSheet;
    sf::Texture runSheet;
};