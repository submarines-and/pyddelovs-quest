#pragma once
#include "game.h"

class TextureManager
{
public:
    static SDL_Texture *loadTexture(const char *filename);
};