#pragma once
#include <SDL2/SDL.h>
#include "vector2d.h"

class Camera {
private:
    SDL_Rect windowSize;

public:
    SDL_Rect position;
    void setPosition(int w, int h);
    void update(Vector2d playerPosition);
};