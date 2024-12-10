#pragma once
#include <SFML/Graphics.hpp>
#include <player.h>
#include "TileMap.h"

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
    void initTileSheet();
    void initTileMap();
    void initInput();

    // main loop handling
    void update();
    void render();
    void processEvents();

    // updates
    void updatePlayer();
    void updatePlayerCollision();
    void updateTileMap();
    void updateInput();

    // renders
    void renderPlayer();
    void renderTileMap();

    sf::RenderWindow window;
    Player *player;
    sf::Texture tileSheet;
    TileMap* tileMap;

    std::map<std::string,sf::Keyboard::Key> keyboardMappings;
};
