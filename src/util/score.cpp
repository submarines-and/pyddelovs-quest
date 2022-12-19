#include "score.h"
#include "components/ai.h"
#include "components/transform.h"
#include "components/sprite.h"

#include "util/level.h"
#include "global.h"

void Score::pickupTreasure(int treasure)
{
    switch (treasure) {
    case Level::SEASHELL:
    case Level::FLOWER:
    case Level::BREAD:
    default:
        score += 20;
        break;
    }

    // spawn krabban klo every 100 points
    if (score % 100 == 0) {

        auto krabbanKlo = global.ecs->createEntity();
        global.ecs->addComponent(krabbanKlo, AI{});
        global.ecs->addComponent(krabbanKlo, Transform{
                                                 .position = Vector2d(0, 0),
                                                 .speed = 100,
                                             });
        global.ecs->addComponent(krabbanKlo, Sprite{
                                                 .filepath = "assets/krabbanklo.png",
                                                 .src = {
                                                     .x = 0,
                                                     .y = 0,
                                                     .h = 32,
                                                     .w = 32,
                                                 },
                                                 .frames = 2,
                                             });
    }
}