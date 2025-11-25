#pragma once
#include <SDL2/SDL.h>

struct Sprite {
    const char* filepath;
    SDL_Rect src;

    SDL_RendererFlip flip = SDL_FLIP_NONE;
    int animationIndex = 0;

    /** Setting to larger than 0 will enable animation in the current spritesheet */
    int frames = 0;
};