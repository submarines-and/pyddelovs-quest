#include "texture-manager.h"

SDL_Texture *TextureManager::loadTexture(const char *filename, SDL_Renderer *renderer)
{
    auto *surface = IMG_Load(filename);
    auto texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    return texture;
}