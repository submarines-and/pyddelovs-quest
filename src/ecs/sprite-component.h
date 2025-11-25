#pragma once
#include "components.h"
#include "SDL2/SDL.h"

class SpriteComponent : public Component
{
private:
    PositionComponent *position;
    SDL_Texture *texture;
    SDL_Rect srcRect, destRect;

public:
    SpriteComponent() = default;
    SpriteComponent(const char *filepath)
    {
        setTexture(filepath);
    }

    void setTexture(const char *filepath)
    {
        texture = TextureManager::loadTexture(filepath);
    }

    void init() override
    {
        position = &entity->getComponent<PositionComponent>();
        srcRect.x = srcRect.y = 0;
        destRect.x = destRect.y = 0;

        srcRect.w = srcRect.h = 32;
        destRect.w = destRect.h = 64;
    }

    void update() override
    {
        destRect.x = position->x();
        destRect.y = position->y();
    }

    void render() override
    {
        TextureManager::render(texture, srcRect, destRect);
    }
};