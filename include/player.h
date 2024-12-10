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
    const sf::FloatRect getGlobalBounds() const;

    // exposed modifiers
    void resetVelocityY();

    // getters and setters
    void setPosition(const float x, const float y);
    bool getMovementState();
    void setMovementState(MovementState value);
    inline const bool& getCanJump() const { return this->canJump; }
    inline void setCanJump(const bool value) { this->canJump = value; }
    void move(const float dir_x, const float dir_y);
    void jump();

private:
    // initialization
    void initVariables();
    void initTextures();
    void initSprite();
    void initAnimations();
    void initPhysics();

    // Movement

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
    bool canJump;

    MovementState animationState;
    sf::Clock animationTimer;
    sf::IntRect currentFrame;
    sf::Sprite sprite;
    sf::Texture idleSheet;
    sf::Texture runSheet;
};