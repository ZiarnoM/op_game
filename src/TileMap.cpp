#include "TileMap.h"

TileMap::TileMap()
{
    this->tileSheet = NULL;
    this->tileSize = 0;

}
TileMap::TileMap(unsigned width, unsigned height, sf::Texture* tile_sheet, unsigned tileSize)
{
    this->tileSheet = tile_sheet;
    this->tileSize = tileSize;

    this->map.resize(width, std::vector<Tile*>(height, NULL));

    for (size_t x = 0; x < width; x++)
    {
        for (size_t y = 0; y < height; y++)
        {
            this->map[x][y] = nullptr;
        }
    }
}

TileMap::~TileMap() {
    for (size_t x = 0; x < this->map.size(); x++) {
        for (size_t y = 0; y < this->map[x].size(); y++) {
            if (this->map[x][y]) {
                delete this->map[x][y];
            }
        }
    }
}

void TileMap::addTile(const unsigned x, const unsigned y) {
    if(x < this->map.size() && x >= 0 && y < this->map[x].size() && y >= 0){
        if(this->map[x][y] == nullptr){
            this->map[x][y] = new Tile(x,y,this->tileSize,this->tileSheet, sf::IntRect(0, 0, this->tileSize, this->tileSize), false);
        }
    }
}

void TileMap::removeTile(const unsigned x, const unsigned y) {
    if(x<this->map.size() && y<this->map[x].size()){
        if(this->map[x][y]){
            if(this->map[x][y] != nullptr){
                delete this->map[x][y];
                this->map[x][y] = nullptr;
            }
        }
    }
}

void TileMap::update() {
    for (auto &x : this->map) {
        for (auto &y : x) {
            if (y) {
                y->update();
            }
        }
    }
}

void TileMap::render(sf::RenderTarget& target) {
    for (auto &x : this->map) {
        for (auto &y : x) {
            if (y){
                y->render(target);
            }
        }
    }
}

