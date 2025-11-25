#pragma once
#include <SDL2/SDL.h>

class CollisionComponent;

class Collision {
public:
    static bool isColliding(const SDL_Rect& a, const SDL_Rect& b);
    static bool isColliding(const CollisionComponent& a, const CollisionComponent& b);
};