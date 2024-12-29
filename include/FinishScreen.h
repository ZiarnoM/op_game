#ifndef OP_GAME_FINISHSCREEN_H
#define OP_GAME_FINISHSCREEN_H
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class FinishScreen {

private:
    sf::Font font;
    sf::Text title;
    sf::Text playAgainButton;

public:
    FinishScreen(float width, float height);
    ~FinishScreen();
    void render(sf::RenderWindow& window);
    bool isPlayAgainButtonPressed(sf::Vector2i mousePos);
};


#endif //OP_GAME_FINISHSCREEN_H
