#pragma once
#include <SDL2/SDL.h>

class Collision {
public:
    static bool isColliding(const SDL_Rect& a, const SDL_Rect& b);
};