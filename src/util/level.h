#pragma once
#include <vector>

struct TilePlacement {
    int x;
    int y;
    int typeId;
};

class Level {
private:
    std::vector<TilePlacement> tiles;

    enum TileType {
        GRASS,
        WATER,
        SAND,
        ROCK,
        SNOW,
        TREE,
    };

    enum Teasures {
        SEASHELL,
    };

    void generateTiles(int width, int height);
    void placeTiles();

public:
    Level(int width, int height);
    TilePlacement getFreeTile(int startX, int startY);
};
