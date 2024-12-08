#pragma once
#include <SFML/Graphics.hpp>

class Game
{
public:
    Game();
    void run();

private:
    void update();
    void render();
    void processEvents();

    sf::RenderWindow window;
    sf::CircleShape player;
};
