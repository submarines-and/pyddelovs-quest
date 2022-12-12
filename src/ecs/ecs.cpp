#include "ecs.h"

void Entity::addGroup(Group g)
{
    groupBitSet[g] = true;
    manager.addToGroup(this, g);
}