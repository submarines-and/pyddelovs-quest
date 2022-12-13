#include "texture-manager.h"

SDL_Texture* TextureManager::loadTexture(const char* filename) {
    auto* surface = IMG_Load(filename);
    auto texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
    SDL_FreeSurface(surface);

    return texture;
}

void TextureManager::render(SDL_Texture* texture, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip) {
    SDL_RenderCopyEx(Game::renderer, texture, &src, &dest, NULL, NULL, flip);
}
