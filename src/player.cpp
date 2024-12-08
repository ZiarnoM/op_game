#include <player.h>

Player::Player()
{
}

Player::Player(float x, float y, sf::Color color) : shape(sf::Vector2f(50.f, 50.f))
{
    shape.setPosition(x, y);
    shape.setFillColor(color);
}

sf::Vector2f Player::getPosition()
{
    return shape.getPosition();
}

sf::Color Player::getColor()
{
    return shape.getFillColor();
}

void Player::setColor(sf::Color color)
{
    shape.setFillColor(color);
}

void Player::setPosition(float x, float y)
{
    shape.setPosition(x, y);
}

void Player::draw(sf::RenderWindow &window)
{
    window.draw(shape);
}
