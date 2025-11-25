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
        score += 1;
        break;
    }

    // spawn krabban klo every X points
    if (score % 3 == 0) {
        auto modifier = (score / 10) % 2 == 0;
        auto x = modifier ? 0 : 2000;
        ;
        auto y = modifier ? 0 : 2000;
        ;

        auto krabbanKlo = global.ecs->createEntity();
        global.ecs->addComponent(krabbanKlo, AI{});
        global.ecs->addComponent(krabbanKlo, Transform{
                                                 .position = Vector2d(x, y),
                                                 .speed = rand() % (200 - 10 + 1) + 10,
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