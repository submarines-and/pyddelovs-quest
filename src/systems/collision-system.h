#pragma once
#include "components/transform.h"
#include "ecs/component-manager.h"
#include "ecs/system.h"
#include "util/vector2d.h"
#include "util/quad-tree.h"
#include "global.h"

class CollisionSystem : public System {
private:
    QuadTree tree;

public:
    void update(Entity player, Vector2d playerPositionBeforeUpdates)
    {
        auto& playerTransform = global.ecs->getComponent<Transform>(player);

        SDL_Rect a{
            .w = playerTransform.width,
            .h = playerTransform.height,
            .x = (int)playerTransform.position.x,
            .y = (int)playerTransform.position.y,
        };

        for (auto e : entities) {
            auto& transform = global.ecs->getComponent<Transform>(e);

            SDL_Rect b{
                .w = transform.width,
                .h = transform.height,
                .x = (int)transform.position.x,
                .y = (int)transform.position.y,
            };

            if (SDL_HasIntersection(&a, &b)) {
                // global.sound.playSoundEffect("sound/character/bounce.wav");
                playerTransform.position = playerPositionBeforeUpdates;
                break;
            }
        }
    }
};