#pragma once
#include "components/transform.h"
#include "ecs/component-manager.h"
#include "ecs/system.h"
#include "util/vector2d.h"
#include "global.h"

class CollisionSystem : public System {
public:
    void update(Entity player, Transform playerTransformBeforeUpdates, float deltaTime)
    {
        auto& playerTransform = global.ecs->getComponent<Transform>(player);

        for (auto e : entities) {
            auto& transform = global.ecs->getComponent<Transform>(e);

            if (Transform::isOverlapping(playerTransform, transform)) {
                // global.sound.playSoundEffect("sound/character/bounce.wav");

                playerTransform.position.x -= playerTransform.direction.x * deltaTime * playerTransform.speed;
                playerTransform.position.y -= playerTransform.direction.y * deltaTime * playerTransform.speed;
                break;
            }
        }
    }
};