#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include "player.h"
#include "map/TileMap.h"
#include "menu/Menu.h"
#include "menu/StartMenu.h"
#include "menu/OptionsMenu.h"
#include "menu/FinishScreen.h"

class Game
{
public:
    Game();
    virtual ~Game();
    void run();

private:
    void initWindow();
    void initMenus();
    void initPlayer();
    void initTileSheet();
    void initTileMap();
    void initInput();
    void initBackground();
    void initClock();

    void update();
    void render();
    void processEvents();

    void updatePlayer();
    void updatePlayerCollision();
    void updateLevel();
    void updateTileMap();
    void updateInput();
    void updateMenu();

    void renderPlayer();
    void renderTileMap();
    void renderBackground();
    void renderMenu();


    void loadLevel(TileMap *tileMap, const std::string &filename);


    sf::RenderWindow window;
    Player *player;

    sf::Texture tileSheet;
    TileMap *tileMap;

    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    StartMenu *startMenu;
    OptionsMenu *optionsMenu;
    FinishScreen* finishScreen;
    Menu* currentMenu;
    bool isMenuActive;

    sf::Clock clock;
    std::fstream times;

    std::map<std::string, sf::Keyboard::Key> keyboardMappings;
};
