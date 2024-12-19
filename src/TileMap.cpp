#include "TileMap.h"

TileMap::TileMap()
{
    this->tileSheet = nullptr;
    this->tileSize = 0;
}
TileMap::TileMap(unsigned width, unsigned height, sf::Texture *tile_sheet, unsigned tileSize)
{
    this->tileSheet = tile_sheet;
    this->tileSize = tileSize;

    for (int i = 0; i < numberOfLevels; i++)
    {
        this->map.push_back(std::vector<std::vector<Tile *>>(width, std::vector<Tile *>(height, nullptr)));
    }
}

TileMap::~TileMap()
{
    for (size_t level = 0; level < this->map.size(); level++)
    {
        for (size_t x = 0; x < this->map[level].size(); x++)
        {
            for (size_t y = 0; y < this->map[level][x].size(); y++)
            {
                if (this->map[level][x][y])
                {
                    delete this->map[level][x][y];
                }
            }
        }
    }
}

void TileMap::addTile(const unsigned x, const unsigned y, const sf::IntRect &textureRect, int level)
{
    if (x < this->map[level].size() && x >= 0 && y < this->map[level][x].size() && y >= 0)
    {
        if (this->map[level][x][y] == nullptr)
        {
            this->map[level][x][y] = new Tile(x, y, this->tileSize, this->tileSheet, textureRect, true);
        }
    }
}

Tile *TileMap::getTile(int level, int x, int y)
{
    return this->map[level][x][y];
}

void TileMap::addLevel()
{
    this->map.push_back(std::vector<std::vector<Tile *>>(this->map[0].size(), std::vector<Tile *>(this->map[0][0].size(), nullptr)));
    numberOfLevels++;
}

// void TileMap::removeTile(const unsigned x, const unsigned y) {
//     if(x<this->map.size() && y<this->map[x].size()){
//         if(this->map[x][y]){
//             if(this->map[x][y] != nullptr){
//                 delete this->map[x][y];
//                 this->map[x][y] = nullptr;
//             }
//         }
//     }
// }

void TileMap::update()
{
    for (auto &x : this->map[currentLevel])
    {
        for (auto &y : x)
        {
            if (y)
            {
                y->update();
            }
        }
    }
}

void TileMap::render(sf::RenderTarget &target)
{
    for (auto &x : this->map[currentLevel])
    {
        for (auto &y : x)
        {
            if (y)
            {
                y->render(target);
            }
        }
    }
}
