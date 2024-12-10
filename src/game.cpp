#include <game.h>
#include <iostream>
#include "LevelLoader.h"

// public methods

Game::Game()
{
    this->initWindow();
    this->initInput();
    this->initPlayer();
    this->initTileSheet();
    this->initTileMap();
}

Game::~Game()
{
    delete this->player;
    delete this->tileMap;
}

void Game::run()
{
    while (this->window.isOpen())
    {
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
    }
}

void Game::render()
{
    this->window.clear();
    this->renderTileMap();
    this->renderPlayer();
    this->window.display();
}

void Game::update()
{
    this->updateInput();
    this->updatePlayer();
    this->updatePlayerCollision();
    this->updateTileMap();
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
    LevelLoader::loadLevel(this->tileMap, "../assets/levels/map1.json");
}

void Game::updateTileMap() {
    this->tileMap->update();
}

void Game::renderTileMap() {
    this->tileMap->render(this->window);
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


