#include <game.h>
#include <iostream>
#include "LevelLoader.h"

// public methods

Game::Game()
{
    this->initWindow();
    this->initBackground();
    this->initInput();
    this->initPlayer();
    this->initTileSheet();
    this->initTileMap();
    this->initStartMenu();
    this->initOptionsMenu();
    this->isMenuActive = true;
}

Game::~Game()
{
    delete this->player;
    delete this->tileMap;
}

void Game::run()
{
    while (this->window.isOpen()) {
        this->processEvents();
        if (this->isMenuActive) {
            this->updateMenu();
            this->renderMenu();
        } else {
            this->update();
            this->render();
        }
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

// main loop handling
void Game::processEvents() {
    sf::Event event;
    while (this->window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            this->window.close();
        }
        if (this->isMenuActive) {
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(this->window);
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (this->startMenu->isOptionButtonPressed(mousePos)) {
                        this->menuState = MenuState::OptionsMenu;
                    } else if (this->startMenu->isPlayButtonPressed(mousePos)) {
                        this->isMenuActive = false;
                    } else if (this->startMenu->isExitButtonPressed(mousePos)) {
                        this->window.close();
                    }
                }
            }
        } else {
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                this->isMenuActive = true;
                this->menuState = MenuState::StartMenu;
            }
        }
    }
}

void Game::render() {
    this->window.clear();
    this->renderBackground();
    if (this->isMenuActive) {
        this->startMenu->draw(this->window);
    } else {
        this->renderTileMap();
        this->renderPlayer();
    }
    this->window.display();
}

void Game::update() {
    if (!this->isMenuActive) {
        this->updateInput();
        this->updatePlayer();
        this->updatePlayerCollision();
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
    if(this->player->getGlobalBounds().left < 0.f)
    {
//check for level numbe
        if(this->tileMap->curreentLevel > 0){
            this->tileMap->curreentLevel--;
            this->player->setPosition(this->window.getSize().x - this->player->getGlobalBounds().width, this->player->getGlobalBounds().top);
        }else{
        this->player->setPosition(0.f, this->player->getGlobalBounds().top);
            }
    }
    if(this->player->getGlobalBounds().left + this->player->getGlobalBounds().width > this->window.getSize().x)
    {
//        check for level number and teleport to next level on left side
        if(this->tileMap->curreentLevel < this->tileMap->numberOfLevels-1){
            this->tileMap->curreentLevel++;
            this->player->setPosition(0.f, this->player->getGlobalBounds().top);
        }else{
            this->player->setPosition(this->window.getSize().x - this->player->getGlobalBounds().width, this->player->getGlobalBounds().top);
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

void Game::initTileMap() {
    this->tileMap = new TileMap(50, 40, &this->tileSheet, 16);
    LevelLoader::loadLevel(this->tileMap, "../assets/levels/level1.json");
}

void Game::updateTileMap() {
    this->tileMap->update();
}

void Game::renderTileMap() {
    this->tileMap->render(this->window);
}

void Game::initBackground() {
    if (!this->backgroundTexture.loadFromFile("../assets/images/background/blue.png")) {
        std::cerr << "Error loading background texture" << std::endl;
    }
    this->backgroundSprite.setTexture(this->backgroundTexture);
}

void Game::renderBackground() {
    sf::Vector2u textureSize = this->backgroundTexture.getSize();
    sf::Vector2u windowSize = this->window.getSize();

    for (unsigned x = 0; x < windowSize.x; x += textureSize.x) {
        for (unsigned y = 0; y < windowSize.y; y += textureSize.y) {
            this->backgroundSprite.setPosition(x, y);
            this->window.draw(this->backgroundSprite);
        }
    }
}

void Game::initInput() {
    this->keyboardMappings["MOVE_LEFT"] = sf::Keyboard::A;
    this->keyboardMappings["MOVE_RIGHT"] = sf::Keyboard::D;
    this->keyboardMappings["JUMP"] = sf::Keyboard::Space;
}

void Game::updateInput() {
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

void Game::initStartMenu() {
    this->startMenu = new StartMenu(800, 640);
}

void Game::initOptionsMenu() {
    this->optionsMenu = new OptionsMenu(800, 640);
}

void Game::updateMenu() {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

    if (menuState == MenuState::StartMenu) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && startMenu->isOptionButtonPressed(mousePos)) {
            menuState = MenuState::OptionsMenu;
        }
    } else if (menuState == MenuState::OptionsMenu) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && optionsMenu->isBackButtonPressed(mousePos)) {
            menuState = MenuState::StartMenu;
        }
    }
}

void Game::renderMenu() {
    window.clear();
    if (menuState == MenuState::StartMenu) {
        startMenu->draw(window);
    } else if (menuState == MenuState::OptionsMenu) {
        optionsMenu->render(window);
    }
    window.display();
}

