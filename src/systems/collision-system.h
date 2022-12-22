#pragma once
#include <vector>
#include "components/transform.h"
#include "components/collision.h"

#include "ecs/component-manager.h"
#include "ecs/system.h"
#include "util/vector2d.h"
#include "global.h"

class CollisionSystem : public System {
public:
    void update(Entity player, Transform playerTransformBeforeUpdates, float deltaTime)
    {
        auto& playerTransform = global.ecs->getComponent<Transform>(player);

        std::vector<Entity> cleanup;

        for (auto e : entities) {
            auto& transform = global.ecs->getComponent<Transform>(e);
            auto& collision = global.ecs->getComponent<Collision>(e);

            if (Transform::isOverlapping(playerTransform, transform)) {

                if (collision.treasureId != -1) {
                    playerTransform.speed += 5;
                    global.score->pickupTreasure(collision.treasureId);
                    global.sound->playSoundEffect("sound/money.wav");
                    cleanup.push_back(e);
                    break;
                }
                else if (collision.damage == 0) {
                    playerTransform.position.x -= playerTransform.direction.x * playerTransform.speed * deltaTime;
                    playerTransform.position.y -= playerTransform.direction.y * playerTransform.speed * deltaTime;
                    global.sound->playSoundEffect("sound/rock.wav");
                }
            }

            if (collision.damage != 0) {
                for (auto c : entities) {
                    if (c == player || c == e) {
                        continue;
                    }

                    auto& cTransform = global.ecs->getComponent<Transform>(c);

                    if (Transform::isOverlapping(cTransform, transform)) {
                        cleanup.push_back(e);
                        cleanup.push_back(c);
                        global.sound->playSoundEffect("sound/impact.wav");
                        break;
                    }
                }
            }
        }

        for (auto e : cleanup) {
            global.ecs->destroyEntity(e);
        }
    }
};