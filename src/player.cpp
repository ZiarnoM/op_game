#include <player.h>

Player::Player()
{
}

Player::Player(float x, float y, sf::Color color) : shape(sf::Vector2f(50.f, 50.f))
{
    this->shape.setPosition(x, y);
    this->shape.setFillColor(color);
}

Player::~Player()
{
}

sf::Vector2f Player::getPosition()
{
    return this->shape.getPosition();
}

sf::Color Player::getColor()
{
    return this->shape.getFillColor();
}

void Player::setColor(sf::Color color)
{
    this->shape.setFillColor(color);
}

void Player::setPosition(float x, float y)
{
    this->shape.setPosition(x, y);
}

void Player::update()
{
}

void Player::render(sf::RenderTarget &target)
{
    target.draw(this->shape);
}
