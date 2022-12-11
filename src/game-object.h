#pragma once
#include "game.h"

class GameObject
{
public:
    GameObject(const char *filename, int x, int y);
    ~GameObject();

    void update();
    void render();

private:
    int xPos;
    int yPos;

    SDL_Texture *texture;
    SDL_Rect srcRect, destRect;
};