#pragma once
#include <vector>
#include "components/collision-component.h"

class CollisionSystem {
private:
    std::vector<CollisionComponent*> colliders;

public:
    void update();
};