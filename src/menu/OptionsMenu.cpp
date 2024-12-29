#include "menu/OptionsMenu.h"

OptionsMenu::OptionsMenu(float width, float height) {
    if(!this->font.loadFromFile("../assets/fonts/Arial.ttf")){
        throw std::runtime_error("Could not load font");
    }
    title.setFont(this->font);
    title.setString("Options");
    title.setCharacterSize(50);
    title.setPosition(width/2 - title.getGlobalBounds().width/2, 50);

    backButton.setFont(this->font);
    backButton.setString("Back");
    backButton.setCharacterSize(30);
    backButton.setPosition(width/2 - backButton.getGlobalBounds().width/2, height - 100);

}

void OptionsMenu::render(sf::RenderWindow &window) {
    window.draw(title);
    window.draw(backButton);
}

bool OptionsMenu::isButtonPressed(sf::Vector2i mousePos) {
    return backButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
}


bool OptionsMenu::isBackButtonPressed(sf::Vector2i mousePos) {
    return backButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
}
