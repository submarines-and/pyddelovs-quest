#pragma once
#include "game.h"

class Entity
{
public:
    Entity(const char *filename, SDL_Renderer *r);
    ~Entity();

    void update();
    void render();

private:
    int x;
    int y;

    SDL_Texture* texture;
    SDL_Rect srcRect;
    SDL_Rect destRect;

    SDL_Renderer* renderer;
};