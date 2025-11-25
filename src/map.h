#pragma once
#include <vector>

struct TilePlacement {
    int x;
    int y;
    int typeId;
};

class Map {
public:
    Map();
    ~Map();

    static void generate(int width, int height);
    static std::vector<TilePlacement> tiles;
};
