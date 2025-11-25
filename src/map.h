#pragma once
#include "game.h"

class Map
{
public:
    Map();
    ~Map();

    /** Available types */
    enum TextureType
    {
        WATER,
        GRASS,
        DIRT,
    };

    void load(int mapArray[20][25]);
    void render();

private:
    SDL_Rect src, dest;
    SDL_Texture *dirt, *grass, *water;

    int currentMap[20][25];
};