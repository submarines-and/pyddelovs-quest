#pragma once
#include <SDL2/SDL.h>
#include "util/vector2d.h"

class Camera {
private:
    SDL_Rect windowSize;

public:
    Camera(int width, int height);
    
    SDL_Rect position;
    void update(Vector2d playerPosition);
};