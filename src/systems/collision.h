#pragma once
#include "components/collision-component.h"
#include "util/vector2d.h"
#include "util/quad-tree.h"

class Collision {
private:
    QuadTree tree;

public:
    Collision() : tree(0, 320, 0, 320) {}

    void update(Vector2d playerPosition);
    void addCollider(CollisionComponent* col);
};