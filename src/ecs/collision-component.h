#pragma once
#include <string>
#include "SDL2/SDL.h"
#include "components.h"

/** Handes collision*/
class CollisionComponent : public Component {

public:
    /** Collidable area */
    SDL_Rect collider;

    /** Save tag of collided object*/
    std::string tag;

    TransformComponent* transform;

    CollisionComponent();
    CollisionComponent(std::string t) {
        tag = t;
    }

    void init() override {

        // add transform if missing
        // this is a safety due to spagetti code
        if (!entity->hasComponent<TransformComponent>()) {
            entity->addComponent<TransformComponent>();
        }

        transform = &entity->getComponent<TransformComponent>();
    }

    /** Update collider box size every frame*/
    void update() override {
        collider.x = static_cast<int>(transform->position.x);
        collider.y = static_cast<int>(transform->position.y);

        collider.w = transform->width * transform->scale;
        collider.h = transform->height * transform->scale;
    }
};