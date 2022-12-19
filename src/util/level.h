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
        SNOW,
    };

    enum Obstacles {
        TREE,
        ROCK,
    };

    void generateTiles(int width, int height);
    void placeTiles(int width, int height);
    void placeObjects();

public:
    enum Teasures {
        SEASHELL,
        FLOWER,
        BREAD,
    };

    Level(int width, int height);
    TilePlacement getFreeTile(int startX, int startY);
};
