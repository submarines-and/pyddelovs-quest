#pragma once
#include "util/vector2d.h"

struct Transform {
    Vector2d position;
    Vector2d direction;

    int height = 32;
    int width = 32;

    int speed = 0;

    static bool isOverlapping(Transform a, Transform b)
    {
        return a.position.x + a.width >= b.position.x &&
               b.position.x + b.width >= a.position.x &&
               a.position.y + a.height >= b.position.y &&
               b.position.y + b.height >= a.position.y;
    }
};