#pragma once
#include "game.h"

class TextureManager
{
public:
    static SDL_Texture *loadTexture(const char *filename);
    static void draw(SDL_Texture* texture, SDL_Rect src, SDL_Rect dest);
};