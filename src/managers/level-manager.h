#pragma once
#include <vector>

struct TilePlacement {
    int x;
    int y;
    int typeId;
};

class LevelManager {
private:
    std::vector<TilePlacement> generateTiles(int width, int height);
    void placeTiles(std::vector<TilePlacement> tiles);

public:
    void generate(int width, int height);
};
