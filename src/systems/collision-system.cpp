#include "collision-system.h"

void CollisionSystem::update()
{

    /*
        // position before updates
        auto playerTransform = player.getComponent<TransformComponent>();

        // bounce on collision
        if (player.hasComponent<CollisionComponent>()) {
            auto playerCollision = player.getComponent<CollisionComponent>();

            for (auto c : colliders) {

                // player cant collide with self
                if (playerCollision.tag == c->tag) {
                    continue;
                }

                if (SDL_HasIntersection(&playerCollision.collider, &c->collider)) {
                    //     global.soundManager.playSoundEffect("sound/character/bounce.wav");
                    player.getComponent<TransformComponent>().position = playerTransform.position;
                    break;
                }
            }
        }
        */
}