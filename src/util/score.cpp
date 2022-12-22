#include "score.h"
#include "entities/krabban-klo.h"
#include "util/level.h"

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

        KrabbanKlo::create(x, y);
    }
}