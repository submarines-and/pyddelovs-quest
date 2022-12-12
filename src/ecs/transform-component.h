#pragma once
#include "ecs.h"

class TransformComponent : public Component
{
private:
    int xPos, yPos;

public:
    /** If no size specified*/
    TransformComponent()
    {
        xPos = 0;
        yPos = 0;
    }

    /** Custom size */
    TransformComponent(int x, int y)
    {
        xPos = x;
        yPos = y;
    }

    int x() { return xPos; }
    int y() { return yPos; }

    void init() override {}

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