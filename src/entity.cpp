#include "entity.h"
#include "texture-manager.h"

Entity::Entity(const char *filename, SDL_Renderer *r)
{
    renderer = r;
    texture = TextureManager::loadTexture(filename, renderer);
}

void Entity::update()
{
    x = 100;
    y = 100;

    srcRect.h = 32;
    srcRect.w = 32;
    srcRect.x = 0;
    srcRect.y = 0;

    destRect.x = x;
    destRect.y = y;
    destRect.w = srcRect.w * 2;
    destRect.h = srcRect.h * 2;
}

void Entity::render()
{
    SDL_RenderCopy(renderer, texture, &srcRect, &destRect);
}
