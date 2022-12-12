#pragma once
#include "../ecs.h"
#include "../vector2d.h"

class TransformComponent : public Component {
public:
    Vector2d position;
    Vector2d velocity;

    int height = 32;
    int width = 32;
    int scale = 1;

    /** Arbitrary */
    int speed = 8;

    /** If no size specified*/
    TransformComponent() {
        position.zero();
    }

    /** Custom position */
    TransformComponent(float x, float y) {
        position.x = x;
        position.y = y;
    }

    /** Custom position AND size */
    TransformComponent(float x, float y, int w, int h, int sc) {
        position.x = x;
        position.y = y;
        width = w;
        height = h;
        scale = sc;
    }

    void init() override {
        velocity.zero();
    }

    void update() override {
        position.x += velocity.x * speed;
        position.y += velocity.y * speed;
    }
};