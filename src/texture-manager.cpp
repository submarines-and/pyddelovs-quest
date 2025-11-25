#include "texture-manager.h"

SDL_Texture *TextureManager::loadTexture(const char *filename)
{
    auto *surface = IMG_Load(filename);
    auto texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
    SDL_FreeSurface(surface);

    return texture;
}