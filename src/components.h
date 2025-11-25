#pragma once
#include "ecs.h"

class PositionComponent : public Component
{
private:
    int xPos, yPos;

public:
    int x() { return xPos; }
    int y() { return yPos; }

    void init() override
    {
        xPos = 0;
        yPos = 0;
    }

    void update() override
    {
        yPos++;
        xPos++;
    }

    void setPosition(int x, int y)
    {
        xPos = x;
        yPos = y;
    }
};