#ifndef OP_GAME_OPTIONSMENU_H
#define OP_GAME_OPTIONSMENU_H
#pragma once
#include <SFML/Graphics.hpp>

class OptionsMenu{
private:
    sf::Font font;
    sf::Text title;
    sf::Text backButton;

public:
    OptionsMenu(float width, float height);
    ~OptionsMenu();
    void render(sf::RenderWindow &window);
    bool isBackButtonPressed(sf::Vector2i mousePos);
};


#endif //OP_GAME_OPTIONSMENU_H
