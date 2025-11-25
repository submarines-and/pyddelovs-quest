#pragma once
#include "components/ai.h"
#include "components/collision.h"
#include "components/transform.h"
#include "components/sprite.h"
#include "global.h"

class KrabbanKlo {
public:
    static Entity create(int x, int y)
    {
        auto entity = global.ecs->createEntity();
        global.ecs->addComponent(entity, AI{});
        global.ecs->addComponent(entity, Collision{});
        global.ecs->addComponent(entity, Transform{
                                             .position = Vector2d(x, y),
                                             .speed = rand() % (150 - 20 + 1) + 20,
                                         });
        global.ecs->addComponent(entity, Sprite{
                                             .filepath = "assets/krabbanklo.png",
                                             .src = {
                                                 .x = 0,
                                                 .y = 0,
                                                 .h = 32,
                                                 .w = 32,
                                             },
                                             .frames = 2,
                                         });

        return entity;
    }
};