#ifndef OP_GAME_STARTMENU_H
#define OP_GAME_STARTMENU_H
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class StartMenu {

public:
    StartMenu(float width, float height);
    void draw(sf::RenderWindow &window);
    void MoveUp();
    void MoveDown();
    int GetPressedItem() { return selectedItemIndex; }

private:
    int selectedItemIndex;
    sf::Font font;
    std::vector<sf::Text> menuItems;
};


#endif //OP_GAME_STARTMENU_H
