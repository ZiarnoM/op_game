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

    bool getMovementState();
    void setMovementState(MovementState value);

private:
    // initialization
    void initVariables();
    void initTextures();
    void initSprite();
    void initAnimations();
    void initPhysics();

    // Movement
    void move(const float dir_x, const float dir_y);
    void updateMovement();
    void updatePhysics();

    // Animations
    void updateAnimations();

    // fields

    sf::Vector2f velocity;
    float minVelocity;
    float maxVelocity;
    float accelerationRate;
    float decelerationRate;
    float gravity;
    float maxFallSpeed;

    MovementState animationState;
    sf::Clock animationTimer;
    sf::IntRect currentFrame;
    sf::Sprite sprite;
    sf::Texture idleSheet;
    sf::Texture runSheet;
};