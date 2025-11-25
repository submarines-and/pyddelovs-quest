#include "entity.h"
#include "texture-manager.h"

Entity::Entity(const char *filename, int x, int y)
{
    texture = TextureManager::loadTexture(filename);

    xPos = x;
    yPos = y;
}

void Entity::update()
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

void Entity::render()
{
    SDL_RenderCopy(Game::renderer, texture, &srcRect, &destRect);
}
