#include <string>
#include <nlohmann/json.hpp>
#include "TileMap.h"

class LevelLoader {
public:
    static void loadLevel(TileMap* tileMap, const std::string& filename);
};