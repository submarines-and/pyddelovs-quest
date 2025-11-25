#include "global.h"

#include "components/collision.h"
#include "components/player.h"
#include "components/transform.h"
#include "components/sprite.h"

#include "systems/collision-system.h"
#include "systems/keyboard-system.h"
#include "systems/sprite-system.h"
#include "systems/transform-system.h"

#include "util/level.h"

/** Init global state and make accessible for main function. */
static Global global_instance;
Global& global = global_instance;

int main()
{
    const int width = 1280;
    const int height = 1280;

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        global.window = SDL_CreateWindow("Pyddelovs Quest", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
        global.renderer = SDL_CreateRenderer(global.window, -1, 0);
    }

    global.sound = new Sound();

    global.ecs = new ECS();
    global.ecs->init();

    // register all components
    global.ecs->registerComponent<Player>();
    global.ecs->registerComponent<Transform>();
    global.ecs->registerComponent<Sprite>();
    global.ecs->registerComponent<Collision>();

    auto spriteSystem = global.ecs->registerSystem<SpriteSystem>();
    {
        Signature signature;
        signature.set(global.ecs->getComponentType<Sprite>());
        signature.set(global.ecs->getComponentType<Transform>());
        global.ecs->setSystemSignature<SpriteSystem>(signature);
    }

    auto transformSystem = global.ecs->registerSystem<TransformSystem>();
    {
        Signature signature;
        signature.set(global.ecs->getComponentType<Transform>());
        global.ecs->setSystemSignature<TransformSystem>(signature);
    }
    transformSystem->init(width, height);

    auto collisionSystem = global.ecs->registerSystem<CollisionSystem>();
    {
        Signature signature;
        signature.set(global.ecs->getComponentType<Collision>());
        global.ecs->setSystemSignature<CollisionSystem>(signature);
    }

    auto keyboardSystem = global.ecs->registerSystem<KeyboardSystem>();
    {
        Signature signature;
        signature.set(global.ecs->getComponentType<Player>());
        signature.set(global.ecs->getComponentType<Transform>());
        global.ecs->setSystemSignature<KeyboardSystem>(signature);
    }

    // create level
    Level level = Level(width * 2, height * 2);
    auto freeTile = level.getFreeTile(width / 2, height / 2);

    // create pyddelov
    auto player = global.ecs->createEntity();
    global.ecs->addComponent(player, Player{});
    global.ecs->addComponent(player, Transform{
                                         .position = Vector2d(freeTile.x, freeTile.y),
                                         .speed = 200,
                                     });
    global.ecs->addComponent(player, Sprite{
                                         .filepath = "assets/pyddelov.png",
                                         .src = {
                                             .x = 0,
                                             .y = 0,
                                             .h = 32,
                                             .w = 32,
                                         },
                                         .frames = 3,
                                     });

    // main loop
    const int fps = 1000 / 60;
    int delta = 0;

    while (!SDL_QuitRequested()) {
        int start = SDL_GetTicks();

        /** Player position before updates*/
        auto playerTransform = global.ecs->getComponent<Transform>(player);

        keyboardSystem->update();
        transformSystem->update(playerTransform.position, float(delta / 1000.0f));
        collisionSystem->update(player, playerTransform, float(delta / 1000.0f));
        spriteSystem->update();

        delta = SDL_GetTicks() - start;

        if (delta < fps) {
            SDL_Delay(fps - delta);
        }
    }

    SDL_DestroyWindow(global.window);
    SDL_DestroyRenderer(global.renderer);
    SDL_Quit();

    return 0;
}