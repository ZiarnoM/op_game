#include <game.h>

const float STARTING_X = 50.f;
const float STARTING_Y = 50.f;
const sf::Color STARTING_COLOR = sf::Color::Blue;

Game::Game() : window(sf::VideoMode(800, 600), "OP Game"), player(400.f - STARTING_X, 300.f - STARTING_Y, STARTING_COLOR)
{
}

void Game::run()
{
    while (window.isOpen())
    {
        processEvents();
        render();
    }
}

void Game::processEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }
    }
}

void Game::render()
{
    window.clear();
    player.draw(window);
    window.display();
}