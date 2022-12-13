#pragma once
#include <SDL2/SDL.h>
#include "../ecs.h"
#include "../texture-manager.h"
#include "transform-component.h"

class TileComponent : public Component {
public:
    SDL_Texture* texture;
    SDL_Rect srcRect, destRect;

    /** Available tile types */
    enum TileType {
        GRASS,
        ROCK,
        WATER,
        SAND,
        SNOW
    };

    TileComponent() = default;
    TileComponent(int x, int y, int tileId)
    {
        // load spritesheet
        texture = TextureManager::loadTexture("assets/terrain.png");

        srcRect.w = srcRect.h = destRect.w = destRect.h = 32;

        int spriteRows = 3;
        srcRect.y = (tileId / spriteRows) * 32;
        srcRect.x = (tileId % spriteRows) * 32;





        destRect.x = x;
        destRect.y = y;
    }

    ~TileComponent()
    {
        SDL_DestroyTexture(texture);
    }

    void render() override
    {
        TextureManager::render(texture, srcRect, destRect, SDL_FLIP_NONE);
    }
};
