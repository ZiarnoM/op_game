#pragma once
#define OP_GAME_TILEMAP_H
#include "Tile.h"

class TileMap {
private:
    std::vector<std::vector<std::vector<Tile*>>> map;
    sf::Texture* tileSheet;
    unsigned tileSize;

public:
    TileMap();
    TileMap(unsigned width, unsigned height, sf::Texture* tile_sheet, unsigned tileSize);
    ~TileMap();

    inline const unsigned& getTileSize() const { return this->tileSize; }
    void addTile(const unsigned x, const unsigned y, const sf::IntRect& textureRect, int level);
    void removeTile(const unsigned x, const unsigned y);
    void addLevel();

    void update();
    void render(sf::RenderTarget& target);

    int numberOfLevels = 1;
    int curreentLevel = 0;

};


