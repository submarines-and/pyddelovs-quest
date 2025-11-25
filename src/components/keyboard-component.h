#pragma once
#include "component.h"
#include "transform-component.h"
#include "sprite-component.h"

class KeyboardComponent : public Component {
private:
    SDL_Event event;

public:
    TransformComponent* transform;
    SpriteComponent* sprite;

    void init() override;
    void update() override;
};