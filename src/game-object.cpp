#include "game-object.h"
#include "texture-manager.h"

GameObject::GameObject(const char *filename, int x, int y)
{
    texture = TextureManager::loadTexture(filename);

    xPos = x;
    yPos = y;
}

void GameObject::update()
{

    srcRect.h = 32;
    srcRect.w = 32;
    srcRect.x = 0;
    srcRect.y = 0;

    destRect.x = xPos;
    destRect.y = yPos;
    destRect.w = srcRect.w * 2;
    destRect.h = srcRect.h * 2;
}

void GameObject::render()
{
    SDL_RenderCopy(Game::renderer, texture, &srcRect, &destRect);
}
