#include "collision-component.h"

void CollisionComponent::init()
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
void CollisionComponent::update()
{
    collider.x = static_cast<int>(transform->position.x);
    collider.y = static_cast<int>(transform->position.y);

    collider.w = transform->width;
    collider.h = transform->height;
}
