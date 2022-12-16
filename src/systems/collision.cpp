#include "collision.h"
#include "components/transform-component.h"
#include "components/collision-component.h"
#include "components/keyboard-component.h"
#include "global.h"

void Collision::update(Vector2d playerPosition)
{

    // position before updates

    // bounce on collision
    if (global.pyddelov->hasComponent<CollisionComponent>()) {
        auto player = global.pyddelov->getComponent<CollisionComponent>();

        auto colliders = tree.getObjectsAt(playerPosition.x, playerPosition.y);

        for (auto c : colliders) {

            // dont collide with yourself
            if (player.collider.x == c->x && player.collider.y == c->y) {
                continue;
            }

            if (SDL_HasIntersection(&player.collider, c)) {
                // global.sound.playSoundEffect("sound/character/bounce.wav");
                global.pyddelov->getComponent<TransformComponent>().position = playerPosition;
                break;
            }
        }
    }
}

void Collision::addCollider(CollisionComponent* col)
{
    tree.addObject(&col->collider);
}
