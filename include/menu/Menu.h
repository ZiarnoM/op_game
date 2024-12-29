// Menu.h
#pragma once
#include <SFML/Graphics.hpp>

class Menu {
public:
    virtual ~Menu() = default;
    virtual void render(sf::RenderWindow& window) = 0;
    virtual bool isButtonPressed(sf::Vector2i mousePos) = 0;
};