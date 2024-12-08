#include <game.h>

Game::Game() : window(sf::VideoMode(800, 600), "OP Game"), player(50.f)
{
    player.setFillColor(sf::Color::Blue);
    player.setPosition(400.f - player.getRadius(), 300.f - player.getRadius());
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
    window.draw(player);
    window.display();
}