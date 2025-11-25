#pragma once

#include "components/transform.h"
#include "ecs/system.h"
#include "global.h"
#include "util/vector2d.h"

class AISystem : public System {

public:
    void update(Vector2d playerPosition)
    {

        for (auto e : entities) {
            auto& transform = global.ecs->getComponent<Transform>(e);

            transform.direction.x = playerPosition.x > transform.position.x ? 1 : -1;
            transform.direction.y = playerPosition.y > transform.position.y ? 1 : -1;

            transform.direction.normalize();
        }
    }
};