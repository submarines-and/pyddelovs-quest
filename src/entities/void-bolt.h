#pragma once
#include "components/collision.h"
#include "components/transform.h"
#include "components/sprite.h"
#include "global.h"

class VoidBolt {
public:
    static Entity create(int startX, int startY)
    {
        int mouseX;
        int mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);

        mouseX -= startX;
        mouseY -= startY;

        auto entity = global.ecs->createEntity();
        global.ecs->addComponent(entity, Collision{.damage = 1});
        global.ecs->addComponent(entity, Transform{
                                             .position = Vector2d(startX, startY),
                                             .speed = 150,
                                             .direction = Vector2d(mouseX, mouseY).normalize()});
        global.ecs->addComponent(entity, Sprite{
                                             .filepath = "assets/projectiles.png",
                                             .src = {
                                                 .x = 0,
                                                 .y = 0,
                                                 .h = 32,
                                                 .w = 32,
                                             },
                                         });

      //  global.sound->playSoundEffect("sound/shoot.wav");

        return entity;
    }
};