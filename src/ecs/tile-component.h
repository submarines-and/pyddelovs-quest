#pragma once
#include <SDL2/SDL.h>
#include "ecs.h"
#include "transform-component.h"
#include "sprite-component.h"

class TileComponent : public Component {
public:
    TransformComponent* transform;
    SpriteComponent* sprite;

    SDL_Rect tileRect;
    int tileId;
    const char* filepath;

    /** Available tile types */
    enum TextureType {
        WATER,
        ROCK,
        GRASS,
        SAND,
    };

    TileComponent() = default;
    TileComponent(int x, int y, int w, int h, int id)
    {
        tileRect.x = x;
        tileRect.y = y;
        tileRect.w = w;
        tileRect.h = h;

        tileId = id;

        switch (tileId) {
        default:
        case WATER:
            filepath = "assets/water.png";
            break;

        case ROCK:
            filepath = "assets/rock.png";
            break;

        case SAND:
            filepath = "assets/sand.png";
            break;

        case GRASS:
            filepath = "assets/grass.png";
            break;
        }
    }

    void init() override
    {
        entity->addComponent<TransformComponent>((float)tileRect.x, (float)tileRect.y, (float)tileRect.w, (float)tileRect.h, 1);
        transform = &entity->getComponent<TransformComponent>();

        entity->addComponent<SpriteComponent>(filepath);
        sprite = &entity->getComponent<SpriteComponent>();
    }
};
