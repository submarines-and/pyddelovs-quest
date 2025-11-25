#pragma once
#include "util/vector2d.h"

struct Transform {
    Vector2d position;
    Vector2d velocity;

    int height = 32;
    int width = 32;

    int speed = 0;
};