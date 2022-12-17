#pragma once
#include <SDL2/SDL.h>
#include "component.h"
#include "util/vector2d.h"

class TileComponent : public Component {
public:
    SDL_Texture* texture;
    SDL_Rect srcRect, destRect;
    Vector2d tilePosition;

    /** Available tile types */
    enum TileType {
        GRASS,
        WATER,
        SAND,
        ROCK,
        SNOW,
        TREE,
        FLOWER,
    };

    TileComponent() = default;
    TileComponent(int x, int y, int w, int h, int tileId);
    ~TileComponent();

    void init() override;
    void render() override;
    void update() override;
};
