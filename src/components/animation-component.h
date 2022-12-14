#pragma once

struct Animation {
    int index;
    int frames;
    int animationSpeed;

    Animation() = default;

    Animation(int i, int f, int s)
    {
        index = i;
        frames = f;
        animationSpeed = s;
    };
};