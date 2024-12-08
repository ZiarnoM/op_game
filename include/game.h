#pragma once
#include <SFML/Graphics.hpp>
#include <player.h>

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
    Player player;
};
