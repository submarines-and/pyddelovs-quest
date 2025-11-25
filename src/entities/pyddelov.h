#pragma once
#include "components/player.h"
#include "components/transform.h"
#include "components/sprite.h"
#include "global.h"

class Pyddelov {
public:
    static Entity create(int x, int y)
    {
        auto entity = global.ecs->createEntity();
        global.ecs->addComponent(entity, Player{});
        global.ecs->addComponent(entity, Transform{
                                             .position = Vector2d(x, y),
                                             .speed = 100,
                                         });
        global.ecs->addComponent(entity, Sprite{
                                             .filepath = "assets/pyddelov.png",
                                             .src = {
                                                 .x = 0,
                                                 .y = 0,
                                                 .h = 32,
                                                 .w = 32,
                                             },
                                             .frames = 3,
                                         });

        return entity;
    }
};