#include "OptionsMenu.h"

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

bool OptionsMenu::isBackButtonPressed(sf::Vector2i mousePos) {
    sf::FloatRect backButtonBounds = backButton.getGlobalBounds();
    if(backButtonBounds.contains(mousePos.x, mousePos.y)){
        return true;
    }
    return false;
}
