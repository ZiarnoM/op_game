#include <game.h>

// public methods

Game::Game()
{
    this->initWindow();
    this->initPlayer();
}

Game::~Game()
{
    delete this->player;
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
    this->window.create(sf::VideoMode(800, 600), "OP Game");
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
    this->renderPlayer();
    this->window.display();
}

void Game::update()
{
    this->updatePlayer();
}

// player stuff
void Game::updatePlayer()
{
    this->player->update();
}

void Game::renderPlayer()
{
    this->player->render(this->window);
}
