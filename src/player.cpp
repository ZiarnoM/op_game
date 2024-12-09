#include <player.h>
#include <iostream>

// Public
// constructors and destructors
Player::Player()
{
    this->speed = 5.f;
    this->initTextures();
    this->initSprite();
}

Player::~Player()
{
}

// general methods
void Player::update()
{
    this->updateMovement();
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

// Private
// updates
void Player::updateMovement()
{
    const float speed = this->getSpeed();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    {
        this->sprite.move(-speed, 0.f);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        this->sprite.move(speed, 0.f);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
    {
        this->sprite.move(0.f, -speed);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
    {
        this->sprite.move(0.f, speed);
    }
}

// initialization

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
}
