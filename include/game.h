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
    // initialization
    void initWindow();
    void initPlayer();

    // main loop handling
    void update();
    void render();
    void processEvents();

    // updates
    void updatePlayer();
    void updatePlayerCollision();

    // renders
    void renderPlayer();

    sf::RenderWindow window;
    Player *player;
};
