#include "LevelLoader.h"
#include <fstream>

void LevelLoader::loadLevel(TileMap* tileMap, const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }
    nlohmann::json levelData;
    file >> levelData;
    file.close();

    const auto& layer = levelData["layers"][0];
    const auto& tiles = layer["data"];
    unsigned width = layer["width"];
    unsigned height = layer["height"];

    for (unsigned y = 0; y < height; ++y) {
        for (unsigned x = 0; x < width; ++x) {
            unsigned tileIndex = y * width + x;
            unsigned tileId = tiles[tileIndex];
            if (tileId != 0) {
                unsigned textureX = (tileId - 1) % 22 * tileMap->getTileSize();
                unsigned textureY = (tileId - 1) / 22 * tileMap->getTileSize();
                sf::IntRect textureRect(textureX, textureY, tileMap->getTileSize(), tileMap->getTileSize());
                tileMap->addTile(x, y, textureRect);
            }
        }
    }
}