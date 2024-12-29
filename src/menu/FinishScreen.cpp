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

    subtitle1.setFont(this->font);
    subtitle1.setString("Your current time:");
    subtitle1.setCharacterSize(50);
    subtitle1.setPosition(width / 2 - subtitle1.getGlobalBounds().width / 2, 150);

    currentTime.setFont(this->font);
    currentTime.setCharacterSize(50);
    currentTime.setPosition((width - 145) / 2, 200);
    
    subtitle2.setFont(this->font);
    subtitle2.setString("Your best times:");
    subtitle2.setCharacterSize(50);
    subtitle2.setPosition(width / 2 - subtitle2.getGlobalBounds().width / 2, 300);

    bestTimes.setFont(this->font);
    bestTimes.setCharacterSize(50);
    bestTimes.setPosition((width - 145) / 2, 350);

    playAgainButton.setFont(this->font);
    playAgainButton.setString("Play again");
    playAgainButton.setCharacterSize(50);
    playAgainButton.setPosition(width / 2 - playAgainButton.getGlobalBounds().width / 2, height - 100);
}

void FinishScreen::render(sf::RenderWindow& window) {
    window.draw(title);
    window.draw(subtitle1);
    window.draw(currentTime);
    window.draw(subtitle2);
    window.draw(bestTimes);
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

void FinishScreen::displayTimes(std::vector<sf::Time> times, sf::Time time)
{
    std::sort(times.begin(), times.end(), [](const sf::Time& a, const sf::Time& b) {
        return a < b;
        });
    currentTime.setString(std::to_string(time.asMilliseconds()));
    if (times.size() > 2)
    {
        bestTimes.setString(std::to_string(times[0].asMilliseconds()) + "\n" + std::to_string(times[1].asMilliseconds()) + "\n" + std::to_string(times[2].asMilliseconds()));
    }
    else if (times.size() == 2)
    {
        bestTimes.setString(std::to_string(times[0].asMilliseconds()) + "\n" + std::to_string(times[1].asMilliseconds()));
    }
    else
    {
        bestTimes.setString(std::to_string(times[0].asMilliseconds()));
    }
}
