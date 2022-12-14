#pragma once
#include "SDL2/SDL.h"
#include <string>

#include "managers/entity-manager.h"
#include "transform-component.h"
#include "global.h"

/** Handes collision*/
class CollisionComponent : public Component {

public:
    /** Collidable area */
    SDL_Rect collider;

    /** Save tag of collided object*/
    std::string tag;

    TransformComponent* transform;

    CollisionComponent() = default;
    CollisionComponent(std::string t)
    {
        tag = t;
    }

    void init() override
    {

        // add transform if missing
        // this is a safety due to spagetti code
        if (!entity->hasComponent<TransformComponent>()) {
            entity->addComponent<TransformComponent>();
        }

        transform = &entity->getComponent<TransformComponent>();

        // add to game, move to system??
     //   Game::colliders.push_back(this);
    }

    /** Update collider box size every frame*/
    void update() override
    {
        collider.x = static_cast<int>(transform->position.x);
        collider.y = static_cast<int>(transform->position.y);

        collider.w = transform->width;
        collider.h = transform->height;
    }
};