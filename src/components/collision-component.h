#pragma once
#include <SDL2/SDL.h>
#include <string>
#include "character/entity.h"
#include "transform-component.h"


/** Handes collision*/
class CollisionComponent : public Component {
private:
    SDL_Rect collider;
    TransformComponent* transform;

public:
    void init() override;
    void update() override;
};