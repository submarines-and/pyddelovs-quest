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

void init(const char* title, int x, int y, int width, int height, bool fullscreen)
{
}

int main()
{
    const int fps = 60;
    const int frameDelay = 1000 / fps;
    const int width = 1280;
    const int height = 1280;

    Uint32 frameStart;
    int frameTime;

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        global.window = SDL_CreateWindow("Pyddelovs Quest", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
        global.renderer = SDL_CreateRenderer(global.window, -1, 0);
    }

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
    Level level;
    level.generateTiles(width * 2, height * 2);
    level.placeTiles();
    auto freeTile = level.getFreeTile(width / 2, height / 2);

    // create pyddelov
    auto player = global.ecs->createEntity();
    global.ecs->addComponent(player, Player{});
    global.ecs->addComponent(player, Transform{
                                         .position = Vector2d(freeTile.x, freeTile.y),
                                         .speed = 2,
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
    while (!SDL_QuitRequested()) {
        frameStart = SDL_GetTicks();

        auto playerPositionBeforeUpdates = global.ecs->getComponent<Transform>(player).position;

        keyboardSystem->update();
        transformSystem->update(playerPositionBeforeUpdates);
        collisionSystem->update(player, playerPositionBeforeUpdates);
        spriteSystem->update();

        frameTime = SDL_GetTicks() - frameStart;

        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    SDL_DestroyWindow(global.window);
    SDL_DestroyRenderer(global.renderer);
    SDL_Quit();

    return 0;
}