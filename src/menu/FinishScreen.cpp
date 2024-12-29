#include "menu/FinishScreen.h"
#include<iostream>

FinishScreen::FinishScreen(float width, float height) {
    if (!this->font.loadFromFile("../assets/fonts/Arial.ttf")) {
        throw std::runtime_error("Could not load font");
    }
    title.setFont(this->font);
    title.setString("CONGRATULATIONS");
    title.setCharacterSize(50);
    title.setPosition(width / 2 - title.getGlobalBounds().width / 2, 50);

    playAgainButton.setFont(this->font);
    playAgainButton.setString("Play again");
    playAgainButton.setCharacterSize(30);
    playAgainButton.setPosition(width / 2 - playAgainButton.getGlobalBounds().width / 2, height - 100);
}

void FinishScreen::render(sf::RenderWindow& window) {
    window.draw(title);
    window.draw(playAgainButton);
}

bool FinishScreen::isPlayAgainButtonPressed(sf::Vector2i mousePos) {
    sf::FloatRect backButtonBounds = playAgainButton.getGlobalBounds();
    if (backButtonBounds.contains(mousePos.x, mousePos.y)) {
        return true;
    }
    return false;
}

bool FinishScreen::isButtonPressed(sf::Vector2i mousePos) {
    return playAgainButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
}
