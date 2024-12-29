// FinishScreen.h
#pragma once
#include "Menu.h"

class FinishScreen : public Menu {
public:
    FinishScreen(float width, float height);
    void render(sf::RenderWindow& window) override;
    bool isButtonPressed(sf::Vector2i mousePos) override;
    bool isPlayAgainButtonPressed(sf::Vector2i mousePos);

private:
    sf::Font font;
    sf::Text title;
    sf::Text playAgainButton;
};