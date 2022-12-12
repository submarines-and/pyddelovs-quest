#pragma once
#include "../vector2d.h"

class TransformComponent : public Component {
public:
    Vector2d position;
    Vector2d velocity;
    int speed = 3;

    /** If no size specified*/
    TransformComponent() {
        position.x = 0;
        position.y = 0;
    }

    /** Custom size */
    TransformComponent(float x, float y) {
        position.x = x;
        position.y = y;
    }

    void init() override {
        velocity.x = velocity.y = 0;
    }

    void update() override {
        position.x += velocity.x * speed;
        position.y += velocity.y * speed;
    }
};