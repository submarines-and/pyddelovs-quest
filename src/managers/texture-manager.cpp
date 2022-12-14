#include "texture-manager.h"
#include "global.h"

SDL_Texture* TextureManager::loadTexture(const char* filepath)
{
    // check cache
    if (textures.count(filepath)) {
        return textures[filepath];
    }

    auto* surface = IMG_Load(filepath);
    auto texture = SDL_CreateTextureFromSurface(global.renderer, surface);
    SDL_FreeSurface(surface);

    textures.emplace(filepath, texture);
    return texture;
}

void TextureManager::render(SDL_Texture* texture, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip)
{
    SDL_RenderCopyEx(global.renderer, texture, &src, &dest, 0, NULL, flip);
}
