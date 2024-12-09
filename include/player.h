#pragma once
#include <SFML/Graphics.hpp>

class Player
{
public:
    Player();
    Player(float x, float y, sf::Color color);
    virtual ~Player();

    sf::Vector2f getPosition();
    sf::Color getColor();

    void setPosition(float x, float y);
    void setColor(sf::Color color);

    void update();
    void render(sf::RenderTarget &target);

private:
    sf::RectangleShape shape;
};