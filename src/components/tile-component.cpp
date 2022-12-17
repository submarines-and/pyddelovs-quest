#include "tile-component.h"
#include "transform-component.h"
#include "global.h"

TileComponent::TileComponent(int x, int y, int w, int h, int tileId)
{

    // load spritesheet
    texture = global.textures.loadTexture("assets/terrain.png");

    // sprite sheets are always 32x32
    srcRect.w = srcRect.h = 32;

    // int spriteRows = 3;
    // srcRect.x = (tileId % spriteRows) * w;
    // srcRect.y = (tileId / spriteRows) * h;

    srcRect.x = tileId * w;
    srcRect.y = 0;

    destRect.w = w;
    destRect.h = h;
    destRect.x = tilePosition.x = x;
    destRect.y = tilePosition.y = y;
}

TileComponent::~TileComponent()
{
    SDL_DestroyTexture(texture);
}

void TileComponent::init()
{
    if (!entity->hasComponent<TransformComponent>()) {
        entity->addComponent<TransformComponent>(destRect.x, destRect.y, destRect.w, destRect.h, 0);
    }
}

void TileComponent::render()
{
    global.textures.render(texture, srcRect, destRect, SDL_FLIP_NONE);
}

void TileComponent::update()
{
    destRect.x = tilePosition.x - global.camera->position.x;
    destRect.y = tilePosition.y - global.camera->position.y;
}