#pragma once
#include <SDL2/SDL.h>
#include "util/entity-manager.h"
#include "gfx/texture-manager.h"
#include "transform-component.h"
#include "global.h"

class TileComponent : public Component {
public:
    SDL_Texture* texture;
    SDL_Rect srcRect, destRect;
    Vector2d tilePosition;

    /** Available tile types */
    enum TileType {
        GRASS,
        ROCK,
        WATER,
        SAND,
        SNOW
    };

    TileComponent() = default;
    TileComponent(int x, int y, int w, int h, int tileId)
    {

        // load spritesheet
        texture = TextureManager::loadTexture("assets/terrain.png");

        // sprite sheets are always 32x32
        srcRect.w = srcRect.h = 32;

        int spriteRows = 3;
        srcRect.x = (tileId % spriteRows) * w;
        srcRect.y = (tileId / spriteRows) * h;

        destRect.w = w;
        destRect.h = h;
        destRect.x = tilePosition.x = x;
        destRect.y = tilePosition.y = y;
    }

    ~TileComponent()
    {
        SDL_DestroyTexture(texture);
    }

    void init() override
    {
        if (!entity->hasComponent<TransformComponent>()) {
            entity->addComponent<TransformComponent>(destRect.x, destRect.y, destRect.w, destRect.h, 0);
        }
    }

    void render() override
    {
        TextureManager::render(texture, srcRect, destRect, SDL_FLIP_NONE);
    }

    void update() override
    {
        destRect.x = tilePosition.x - global.camera->position.x;
        destRect.y = tilePosition.y - global.camera->position.y;
    }
};
