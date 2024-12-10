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
    void initBackground();

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
    void renderBackground();

    sf::RenderWindow window;
    Player *player;
    sf::Texture tileSheet;
    TileMap* tileMap;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    std::map<std::string,sf::Keyboard::Key> keyboardMappings;


    void loadLevel(TileMap* tileMap, const std::string& filename);
};
