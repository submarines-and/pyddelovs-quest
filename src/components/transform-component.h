#pragma once
#include "component.h"
#include "util/vector2d.h"

class TransformComponent : public Component {
public:
    Vector2d position;
    Vector2d velocity;

    int height = 32;
    int width = 32;
    int speed = 2;

    /** If no size specified*/
    TransformComponent()
    {
        position.zero();
    }

    /** Custom position */
    TransformComponent(float x, float y)
    {
        position.x = x;
        position.y = y;
    }

    /** Custom position AND speed */
    TransformComponent(float x, float y, int s)
    {
        position.x = x;
        position.y = y;
        speed = s;
    }

    /** Custom position AND speed AND size */
    TransformComponent(float x, float y, int w, int h, int s)
    {
        position.x = x;
        position.y = y;
        width = w;
        height = h;
        speed = s;
    }

    void init() override
    {
        velocity.zero();
    }

    void update() override
    {
        position.x += velocity.x * speed;
        position.y += velocity.y * speed;
    }
};