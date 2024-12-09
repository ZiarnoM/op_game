#include <player.h>
#include <iostream>

// Public
// constructors and destructors
Player::Player()
{
    this->initVariables();
    this->initTextures();
    this->initSprite();
    this->initAnimations();
}

Player::~Player()
{
}

// general methods
void Player::update()
{
    this->updateMovement();
    this->updateAnimations();
}

void Player::render(sf::RenderTarget &target)
{
    target.draw(this->sprite);

    // sf::CircleShape circle;
    // circle.setFillColor(sf::Color::Red);
    // circle.setRadius(sf::Color::Red);
    // circle.setFillColor(sf::Color::Red);
}

float Player::getSpeed()
{
    return this->speed;
}

void Player::setSpeed(float value)
{
    this->speed = value;
}

bool Player::getMovementState()
{
    return this->state;
}

void Player::setMovementState(MovementState value)
{
    this->state = value;
}

// Private

// initialization

void Player::initVariables()
{
    this->state = MovementState::Idle;
    this->speed = 3.f;
}

void Player::initTextures()
{
    if (!this->idleSheet.loadFromFile("../assets/images/player/idleSheet.png"))
    {
        std::cout << "Error while loading playerSheet.png" << std::endl;
    }
    if (!this->runSheet.loadFromFile("../assets/images/player/runSheet.png"))
    {
        std::cout << "Error while loading runSheet.png" << std::endl;
    }
}
void Player::initSprite()
{
    this->sprite.setTexture(this->idleSheet);
    this->currentFrame = sf::IntRect(0, 0, 32, 32);
    this->sprite.setTextureRect(this->currentFrame);
    this->sprite.setScale(2.f, 2.f);
}
void Player::initAnimations()
{
    this->animationTimer.restart();
}

// Movement
void Player::updateMovement()
{
    this->setMovementState(MovementState::Idle);
    const float speed = this->getSpeed();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    {
        this->sprite.move(-speed, 0.f);
        this->setMovementState(MovementState::RunLeft);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        this->sprite.move(speed, 0.f);
        this->setMovementState(MovementState::RunRight);
    }
    // else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
    // {
    //     this->sprite.move(0.f, -speed);
    //     this->setMovementState(MovementState::Run);
    // }
    // else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
    // {
    //     this->sprite.move(0.f, speed);
    //     this->setMovementState(MovementState::Run);
    // }
}

// Animations
void Player::updateAnimations()
{
    const float MAX_LEFT_IDLE = 320.f;
    const float MAX_LEFT_RUN = 352.f;
    const float FRAME_WIDTH = 32.f;

    if (this->animationTimer.getElapsedTime().asMilliseconds() >= 50)
    {
        switch (this->state)
        {
        case MovementState::Idle:
            this->sprite.setTexture(this->idleSheet);
            this->currentFrame.left += FRAME_WIDTH;
            if (this->currentFrame.left >= MAX_LEFT_IDLE)
            {
                this->currentFrame.left = 0;
            }
            break;

        case MovementState::RunRight:
            this->sprite.setTexture(this->runSheet);
            this->currentFrame.left += FRAME_WIDTH;
            if (this->currentFrame.left >= MAX_LEFT_RUN)
            {
                this->currentFrame.left = 0;
            }
            this->sprite.setScale(2.f, 2.f);
            this->sprite.setOrigin(0.f, 0.f);

            break;

        case MovementState::RunLeft:
            this->sprite.setTexture(this->runSheet);
            this->currentFrame.left += FRAME_WIDTH;
            if (this->currentFrame.left >= MAX_LEFT_RUN)
            {
                this->currentFrame.left = 0;
            }
            this->sprite.setScale(-2.f, 2.f);
            this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 2.f, 0.f);
            break;

        default:
            break;
        }

        this->animationTimer.restart();
        this->sprite.setTextureRect(this->currentFrame);
    }
}
