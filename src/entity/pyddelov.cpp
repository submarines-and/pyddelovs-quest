#include "pyddelov.h"
#include "components/transform-component.h"
#include "components/sprite-component.h"
#include "components/keyboard-component.h"
#include "components/collision-component.h"
#include "global.h"

Entity* Pyddelov::createPyddelov(int startX, int startY)
{
    auto& player(global.entityManager.addEntity());

    player.addComponent<TransformComponent>(startX, startY);
    player.addComponent<SpriteComponent>("assets/pyddelov.png", 4, 100);
    player.addComponent<KeyboardComponent>();
    player.addComponent<CollisionComponent>();

    return &player;
}
