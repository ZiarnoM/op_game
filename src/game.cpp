#include <game.h>

const float STARTING_X = 50.f;
const float STARTING_Y = 50.f;
const sf::Color STARTING_COLOR = sf::Color::Blue;

void Game::initWindow()
{
    this->window.create(sf::VideoMode(800, 600), "OP Game");
}

void Game::initPlayer()
{
    this->player = new Player(400.f - STARTING_X, 300.f - STARTING_Y, STARTING_COLOR);
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

void Game::updatePlayer()
{
    this->player->update();
}

void Game::renderPlayer()
{
    this->player->render(this->window);
}

Game::Game()
{
    this->initWindow();
    this->initPlayer();
}

Game::~Game()
{
    delete this->player;
}