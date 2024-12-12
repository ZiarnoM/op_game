#include "StartMenu.h"

StartMenu::StartMenu(float width, float height) {
    if (!font.loadFromFile("../assets/fonts/Arial.ttf")) {
        throw std::runtime_error("Could not load font");
    }

    title.setFont(font);
    title.setString("Start Menu");
    title.setCharacterSize(50);
    title.setPosition(width / 2 - title.getGlobalBounds().width / 2, height / 4);

    playButton.setFont(font);
    playButton.setString("Play");
    playButton.setCharacterSize(30);
    playButton.setPosition(width / 2 - playButton.getGlobalBounds().width / 2, height / 2);

    optionsButton.setFont(font);
    optionsButton.setString("Options");
    optionsButton.setCharacterSize(30);
    optionsButton.setPosition(width / 2 - optionsButton.getGlobalBounds().width / 2, height / 2 + 50);

    exitButton.setFont(font);
    exitButton.setString("Exit");
    exitButton.setCharacterSize(30);
    exitButton.setPosition(width / 2 - exitButton.getGlobalBounds().width / 2, height / 2 + 100);
}

void StartMenu::draw(sf::RenderWindow &window) {
    window.draw(title);
    window.draw(playButton);
    window.draw(optionsButton);
    window.draw(exitButton);
}


bool StartMenu::isOptionButtonPressed(sf::Vector2i mousePos) {
    return optionsButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
}

bool StartMenu::isPlayButtonPressed(sf::Vector2i mousePos) {
    return playButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
}

bool StartMenu::isExitButtonPressed(sf::Vector2i mousePos) {
    return exitButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
}
