#pragma once
#include "game.h"

class Entity
{
public:
    Entity(const char *filename, int x, int y);
    ~Entity();

    void update();
    void render();

private:
    int xPos;
    int yPos;

    SDL_Texture* texture;
    SDL_Rect srcRect;
    SDL_Rect destRect;
};