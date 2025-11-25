#pragma once
#include "../vector2d.h"

class TransformComponent : public Component {
public:
    Vector2d position;

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
};