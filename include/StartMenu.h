#ifndef OP_GAME_STARTMENU_H
#define OP_GAME_STARTMENU_H
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class StartMenu {

private:
    sf::Font font;
    sf::Text title;
    sf::Text playButton;
    sf::Text optionsButton;
    sf::Text exitButton;

public:
    StartMenu(float width, float height);
    ~StartMenu();
    void draw(sf::RenderWindow &window);
    int GetPressedItem();
    bool isOptionButtonPressed(sf::Vector2i mousePos);
    bool isPlayButtonPressed(sf::Vector2i mousePos);
    bool isExitButtonPressed(sf::Vector2i mousePos);

};


#endif //OP_GAME_STARTMENU_H
