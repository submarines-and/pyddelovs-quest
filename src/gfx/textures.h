#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <map>

class Textures {
private:
    std::map<const char*, SDL_Texture*> textures;

public:
    SDL_Texture* loadTexture(const char* filepath);
    void render(SDL_Texture* texture, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip);
};