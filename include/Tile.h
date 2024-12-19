#pragma once
#define OP_GAME_TILE_H
#include <SFML/Graphics.hpp>

class Tile
{
private:
    sf::Sprite sprite;
    const bool demaging;

public:
    Tile(const unsigned &grid_pos_x, const unsigned &grid_pos_y, const unsigned &tile_size, sf::Texture *texture_sheet, sf::IntRect texture_rect, const bool damaging = false);
    const sf::FloatRect getGlobalBounds() const;

    void update();
    void render(sf::RenderTarget &target);
};
