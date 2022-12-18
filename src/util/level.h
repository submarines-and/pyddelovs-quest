#pragma once
#include <vector>


struct TilePlacement {
    int x;
    int y;
    int typeId;
};

class Level {
private:
    /** Available tile types */
    enum TileType {
        GRASS,
        WATER,
        SAND,
        ROCK,
        SNOW,
        TREE,
        FLOWER,
    };

public:
    std::vector<TilePlacement> generateTiles(int width, int height);
    void placeTiles(std::vector<TilePlacement> tiles);

};
