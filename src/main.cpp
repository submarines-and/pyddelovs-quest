#include "global.h"

#include "components/ai.h"
#include "components/collision.h"
#include "components/player.h"
#include "components/transform.h"
#include "components/sprite.h"

#include "entities/pyddelov.h"

#include "systems/ai-system.h"
#include "systems/collision-system.h"
#include "systems/keyboard-system.h"
#include "systems/sprite-system.h"
#include "systems/transform-system.h"

#include "util/level.h"
#include "util/score.h"

/** Init global state and make accessible for main function. */
static Global global_instance;
Global& global = global_instance;

int main()
{
    const int width = 960;
    const int height = 960;

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        global.window = SDL_CreateWindow(
            "Pyddelovs Quest",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            width,
            height,
            SDL_RENDERER_PRESENTVSYNC | SDL_GL_RETAINED_BACKING);
        global.renderer = SDL_CreateRenderer(global.window, -1, 0);
    }

    global.sound = new Sound();
    global.score = new Score();

    global.ecs = new ECS();
    global.ecs->init();

    // register all components
    global.ecs->registerComponent<AI>();
    global.ecs->registerComponent<Collision>();
    global.ecs->registerComponent<Player>();
    global.ecs->registerComponent<Sprite>();
    global.ecs->registerComponent<Transform>();

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

    auto aiSystem = global.ecs->registerSystem<AISystem>();
    {
        Signature signature;
        signature.set(global.ecs->getComponentType<AI>());
        signature.set(global.ecs->getComponentType<Transform>());
        global.ecs->setSystemSignature<AISystem>(signature);
    }

    /** Generate level */
    Level level = Level(width * 4, height * 4);
    auto freeTile = level.getFreeTile(width / 2, height / 2);

    /** Create pyddelov */
    auto player = Pyddelov::create(freeTile.x, freeTile.y);

    // main loop
    const int fps = 1000 / 60;
    int delta = 0;

    while (!SDL_QuitRequested()) {
        int start = SDL_GetTicks();

        /** Player position before updates*/
        auto playerTransform = global.ecs->getComponent<Transform>(player);

        keyboardSystem->update();
        aiSystem->update(playerTransform.position);

        transformSystem->update(playerTransform.position, delta / 100.0f);
        collisionSystem->update(player, playerTransform, delta / 100.0f);
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