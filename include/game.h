#pragma once
#include <SFML/Graphics.hpp>
#include <player.h>

class Game
{
public:
    Game();
    virtual ~Game();
    void run();

private:
    void initWindow();
    void initPlayer();

    void update();
    void render();
    void processEvents();

    void updatePlayer();
    void renderPlayer();

    sf::RenderWindow window;
    Player *player;
};
