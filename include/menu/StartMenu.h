#pragma once
#include "Menu.h"

class StartMenu : public Menu {
public:
    StartMenu(float width, float height);
    void render(sf::RenderWindow& window) override;
    bool isButtonPressed(sf::Vector2i mousePos) override;
    bool isOptionButtonPressed(sf::Vector2i mousePos);
    bool isPlayButtonPressed(sf::Vector2i mousePos);
    bool isExitButtonPressed(sf::Vector2i mousePos);

private:
    sf::Font font;
    sf::Text title;
    sf::Text optionButton;
    sf::Text playButton;
    sf::Text exitButton;
};