#include "StartMenu.h"
#include <iostream>

StartMenu::StartMenu(float width, float height)
{
    if (!font.loadFromFile("../assets/fonts/Arial.ttf"))
    {
        std::cout << "Error loading font" << std::endl;
    }

    std::vector<std::string> items = {"Play", "Options", "Exit"};
    for (size_t i = 0; i < items.size(); ++i) {
        sf::Text text;
        text.setFont(font);
        text.setString(items[i]);
        text.setFillColor(i == 0 ? sf::Color::Red : sf::Color::White);
        text.setPosition(sf::Vector2f(width / 2, height / (items.size() + 1) * (i + 1)));
        menuItems.push_back(text);
    }

    selectedItemIndex = 0;
}

void StartMenu::draw(sf::RenderWindow &window)
{
    for (const auto& item : menuItems) {
        window.draw(item);
    }
}

void StartMenu::MoveUp()
{
    if (selectedItemIndex - 1 >= 0)
    {
        menuItems[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex--;
        menuItems[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}

void StartMenu::MoveDown()
{
    if (selectedItemIndex + 1 < menuItems.size())
    {
        menuItems[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex++;
        menuItems[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}


