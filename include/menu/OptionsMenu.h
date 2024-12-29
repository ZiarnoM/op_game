// OptionsMenu.h
#pragma once
#include "Menu.h"

class OptionsMenu : public Menu {
public:
    OptionsMenu(float width, float height);
    void render(sf::RenderWindow& window) override;
    bool isButtonPressed(sf::Vector2i mousePos) override;
    bool isBackButtonPressed(sf::Vector2i mousePos);

private:
    sf::Font font;
    sf::Text title;
    sf::Text backButton;
};