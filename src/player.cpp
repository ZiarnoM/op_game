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
}

float Player::getSpeed()
{
    return this->speed;
}

void Player::setSpeed(float value)
{
    this->speed = value;
}

bool Player::getIsMoving()
{
    return this->isMoving;
}

void Player::setIsMoving(bool value)
{
    this->isMoving = value;
}

// Private

// initialization

void Player::initVariables()
{
    this->isMoving = false;
    this->speed = 3.f;
}

void Player::initTextures()
{
    if (!this->idleSheet.loadFromFile("../assets/images/player/idleSheet.png"))
    {
        std::cout << "Error while loading playerSheet.png" << std::endl;
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
    this->setIsMoving(false);
    const float speed = this->getSpeed();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    {
        this->sprite.move(-speed, 0.f);
        this->setIsMoving(true);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        this->sprite.move(speed, 0.f);
        this->setIsMoving(true);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
    {
        this->sprite.move(0.f, -speed);
        this->setIsMoving(true);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
    {
        this->sprite.move(0.f, speed);
        this->setIsMoving(true);
    }
}

// Animations
void Player::updateAnimations()
{
    if (this->animationTimer.getElapsedTime().asMilliseconds() >= 50)
    {
        if (!this->getIsMoving())
        {
            this->currentFrame.left += 32.f;
            if (this->currentFrame.left >= 320)
            {
                this->currentFrame.left = 0;
            }
        }
        this->animationTimer.restart();
        this->sprite.setTextureRect(this->currentFrame);
    }
}
