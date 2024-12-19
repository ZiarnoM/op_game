#pragma once
#include <SFML/Graphics.hpp>
#include <player.h>
#include "TileMap.h"
#include "StartMenu.h"
#include "OptionsMenu.h"

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
    void initStartMenu();
    void initOptionsMenu();

    // main loop handling
    void update();
    void render();
    void processEvents();

    // updates
    void updatePlayer();
    void updatePlayerCollision();
    void updateLevel();
    void updateTileMap();
    void updateInput();
    void updateMenu();

    // renders
    void renderPlayer();
    void renderTileMap();
    void renderBackground();
    void renderMenu();

    sf::RenderWindow window;
    Player *player;

    sf::Texture tileSheet;
    TileMap *tileMap;

    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    StartMenu *startMenu;
    bool isMenuActive;
    OptionsMenu *optionsMenu;
    enum class MenuState
    {
        StartMenu,
        OptionsMenu
    } menuState;

    std::map<std::string, sf::Keyboard::Key> keyboardMappings;

    void loadLevel(TileMap *tileMap, const std::string &filename);
};
