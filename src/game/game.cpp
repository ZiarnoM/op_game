#include "game/game.h"
#include "map/LevelLoader.h"
#include <iostream>

// public methods

Game::Game()
{
    this->initWindow();
    this->initBackground();
    this->initInput();
    this->initPlayer();
    this->initTileSheet();
    this->initTileMap();
    this->initMenus();
    this->initClock();
    this->isMenuActive = true;
    this->currentMenu = startMenu;

}

Game::~Game()
{
    delete this->player;
    delete this->tileMap;
    delete startMenu;
    this->times.close();
}

void Game::run() {
    while (this->window.isOpen()) {
        this->processEvents();
        this->update();
        this->render();
    }
}

// initialization
void Game::initWindow()
{
    this->window.create(sf::VideoMode(800, 640), "OP Game");
    this->window.setFramerateLimit(144);
}

void Game::initPlayer()
{
    this->player = new Player();
}

void Game::initMenus() {
    this->startMenu = new StartMenu(800, 640);
    this->optionsMenu = new OptionsMenu(800, 640);
    this->finishScreen = new FinishScreen(800, 640);
}

// main loop handling
void Game::processEvents()
{
    sf::Event event;
    while (this->window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            this->window.close();
        }
        if (this->isMenuActive)
        {
            if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2i mousePos = sf::Mouse::getPosition(this->window);
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    if (currentMenu->isButtonPressed(mousePos))
                    {
                        if (currentMenu == startMenu)
                        {
                            if (startMenu->isOptionButtonPressed(mousePos))
                            {
                                currentMenu = optionsMenu;
                            }
                            else if (startMenu->isPlayButtonPressed(mousePos))
                            {
                                this->clock.restart();
                                this->isMenuActive = false;
                            }
                            else if (startMenu->isExitButtonPressed(mousePos))
                            {
                                this->window.close();
                            }
                        }
                        else if (currentMenu == optionsMenu)
                        {
                            if (optionsMenu->isBackButtonPressed(mousePos))
                            {
                                currentMenu = startMenu;
                            }
                        }
                        else if (currentMenu == finishScreen)
                        {
                            if (finishScreen->isPlayAgainButtonPressed(mousePos))
                            {
                                this->clock.restart();
                                this->isMenuActive = false;
                                this->tileMap->currentLevel = 0;
                                this->player->setPosition(0, 0);
                            }
                        }
                    }
                }
            }
        }
        else
        {
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            {
                this->isMenuActive = true;
                this->currentMenu = startMenu;
            }
        }
    }
}
void Game::render()
{
    this->window.clear();
    this->renderBackground();
    if (this->isMenuActive)
    {
        this->renderMenu();
    }
    else
    {
        this->renderTileMap();
        this->renderPlayer();
    }
    this->window.display();
}

void Game::update()
{
    if (!this->isMenuActive)
    {
        this->updateInput();
        this->updatePlayer();
        this->updatePlayerCollision();
        this->updateLevel();
        this->updateTileMap();
    }
}

// player stuff
void Game::updatePlayer()
{
    this->player->update();
}

void Game::updatePlayerCollision()
{
    if (this->player->getGlobalBounds().top + this->player->getGlobalBounds().height > this->window.getSize().y)
    {
        this->player->resetVelocityY();
        this->player->setPosition(
            this->player->getGlobalBounds().left,
            this->window.getSize().y - this->player->getGlobalBounds().height);
    }
    // Check for collision with tiles
    for (int x = 0; x < 50; ++x)
    {
        for (int y = 0; y < 40; ++y)
        {
            Tile *tile = this->tileMap->getTile(this->tileMap->currentLevel, x, y);
            if (tile)
            {
                sf::FloatRect playerBounds = this->player->getGlobalBounds();
                sf::FloatRect tileBounds = tile->getGlobalBounds();

                if (playerBounds.intersects(tileBounds))
                {
                    // Handle collision
                    if (playerBounds.top < tileBounds.top && playerBounds.top + playerBounds.height < tileBounds.top + tileBounds.height && playerBounds.left < tileBounds.left + tileBounds.width && playerBounds.left + playerBounds.width > tileBounds.left)
                    {
                        // Collision from bottom
                        this->player->resetVelocityY();
                        this->player->setCanJump(true);
                        this->player->setPosition(playerBounds.left, tileBounds.top - playerBounds.height);
                    }
                    // else if (playerBounds.top > tileBounds.top && playerBounds.top + playerBounds.height > tileBounds.top + tileBounds.height && playerBounds.left < tileBounds.left + tileBounds.width && playerBounds.left + playerBounds.width > tileBounds.left)
                    // {
                    //     // Collision from top
                    //     this->player->resetVelocityY();
                    //     this->player->setPosition(playerBounds.left, tileBounds.top + tileBounds.height);
                    // }
                    else if (playerBounds.left < tileBounds.left && playerBounds.left + playerBounds.width < tileBounds.left + tileBounds.width && playerBounds.top < tileBounds.top + tileBounds.height && playerBounds.top + playerBounds.height > tileBounds.top)
                    {
                        // Collision from right
                        this->player->resetVelocityX();
                        this->player->setPosition(tileBounds.left - playerBounds.width, playerBounds.top);
                    }
                    else if (playerBounds.left > tileBounds.left && playerBounds.left + playerBounds.width > tileBounds.left + tileBounds.width && playerBounds.top < tileBounds.top + tileBounds.height && playerBounds.top + playerBounds.height > tileBounds.top)
                    {
                        // Collision from left
                        this->player->resetVelocityX();
                        this->player->setPosition(tileBounds.left + tileBounds.width, playerBounds.top);
                    }
                }
            }
        }
    }
}

void Game::updateLevel()
{
    if (this->player->getGlobalBounds().left < 0.f)
    {
        // check for level numbe
        if (this->tileMap->currentLevel > 0)
        {
            this->tileMap->currentLevel--;
            this->player->setPosition(this->window.getSize().x - this->player->getGlobalBounds().width, this->player->getGlobalBounds().top);
        }
        else
        {
            this->player->setPosition(0.f, this->player->getGlobalBounds().top);
        }
    }
    if (this->player->getGlobalBounds().left + this->player->getGlobalBounds().width > this->window.getSize().x)
    {
        //        check for level number and teleport to next level on left side
        if (this->tileMap->currentLevel < this->tileMap->numberOfLevels - 1)
        {
            this->tileMap->currentLevel++;
            this->player->setPosition(0.f, this->player->getGlobalBounds().top);
        }
        else
        {
            sf::Time current_time = clock.getElapsedTime();
            this->times << current_time.asMilliseconds() << std::endl;
            this->finishScreen->displayTimes(this->times, current_time);
            this->isMenuActive = true;
            this->currentMenu = finishScreen;
        }
    }
}

void Game::renderPlayer()
{
    this->player->render(this->window);
}

void Game::initTileSheet()
{
    if (!this->tileSheet.loadFromFile("../assets/images/terrain/terrainSheet.png"))
    {
        std::cerr << "Error loading tile sheet" << std::endl;
    }
}

void Game::initTileMap()
{
    this->tileMap = new TileMap(50, 40, &this->tileSheet, 16);
    LevelLoader::loadLevel(this->tileMap, "../assets/levels/level1.json");
}

void Game::updateTileMap()
{
    this->tileMap->update();
}

void Game::renderTileMap()
{
    this->tileMap->render(this->window);
}

void Game::initBackground()
{
    if (!this->backgroundTexture.loadFromFile("../assets/images/background/blue.png"))
    {
        std::cerr << "Error loading background texture" << std::endl;
    }
    this->backgroundSprite.setTexture(this->backgroundTexture);
}

void Game::renderBackground()
{
    sf::Vector2u textureSize = this->backgroundTexture.getSize();
    sf::Vector2u windowSize = this->window.getSize();

    for (unsigned x = 0; x < windowSize.x; x += textureSize.x)
    {
        for (unsigned y = 0; y < windowSize.y; y += textureSize.y)
        {
            this->backgroundSprite.setPosition(x, y);
            this->window.draw(this->backgroundSprite);
        }
    }
}

void Game::initInput()
{
    this->keyboardMappings["MOVE_LEFT"] = sf::Keyboard::A;
    this->keyboardMappings["MOVE_RIGHT"] = sf::Keyboard::D;
    this->keyboardMappings["JUMP"] = sf::Keyboard::Space;
}

void Game::initClock()
{
    sf::Clock clock;
    this->clock = clock;
    this->times.open("../assets/scores/times.txt", std::ios::in | std::ios::out | std::ios::app);
    if (!times.is_open()) {
        std::cerr << "Failed to open the scores file." << std::endl;
    }    
}

void Game::updateInput()
{
    if (sf::Keyboard::isKeyPressed(this->keyboardMappings["MOVE_LEFT"]))
    {
        this->player->move(-1.f, 0.f);
        this->player->setMovementState(MovementState::RunLeft);
    }
    if (sf::Keyboard::isKeyPressed(this->keyboardMappings["MOVE_RIGHT"]))
    {
        this->player->move(1.f, 0.f);
        this->player->setMovementState(MovementState::RunRight);
    }
    if (sf::Keyboard::isKeyPressed(this->keyboardMappings["JUMP"]))
    {
        if (this->player->getCanJump())
        {
            this->player->jump();
            this->player->setMovementState(MovementState::Jump);
        }
    }
}

void Game::updateMenu()
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

    if (currentMenu == startMenu)
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && startMenu->isOptionButtonPressed(mousePos))
        {
            currentMenu = optionsMenu;
        }
    }
    else if (currentMenu == optionsMenu)
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && optionsMenu->isBackButtonPressed(mousePos))
        {
            currentMenu = startMenu;
        }
    }
}

void Game::renderMenu()
{
    currentMenu->render(this->window);
}
