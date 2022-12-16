#pragma once
#include <SDL2/SDL.h>
#include <string>
#include "component.h"
#include "transform-component.h"


/** Handes collision*/
class CollisionComponent : public Component {
private:
    TransformComponent* transform;

public:
    SDL_Rect collider;

    void init() override;
    void update() override;
};