#pragma once
#include <SFML/Graphics.hpp>

class Player
{
public:
    Player();
    Player(float x, float y, sf::Color color);

    sf::Vector2f getPosition();
    sf::Color getColor();

    void setPosition(float x, float y);
    void setColor(sf::Color color);

    void draw(sf::RenderWindow &window);

private:
    sf::RectangleShape shape;
};