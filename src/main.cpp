#include "global.h"
#include "util/camera.h"
#include "character/pyddelov.h"
#include "components/transform-component.h"
#include "systems/collision.h"

/** Init global state and make accessible for main function. */
static Global global_instance;
Global& global = global_instance;

void init(const char* title, int x, int y, int width, int height, bool fullscreen)
{
    int flags = 0;
    if (fullscreen) {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        global.window = SDL_CreateWindow(title, x, y, width, height, flags);
        global.renderer = SDL_CreateRenderer(global.window, -1, 0);
    }

    global.camera = new Camera(width, height);

    global.collision = new Collision();

    global.level.generate(width * 4, height * 4);

    // create player and place in the moddle
    global.pyddelov = Pyddelov::createPyddelov(width / 2, height / 2);

    // start music
    //  global.sound.playMusic("sound/music/forest.mp3");
}

void update()
{
    auto playerPosition = global.pyddelov->getComponent<TransformComponent>().position;

    global.entityManager.refresh();
    global.entityManager.update();
    global.collision->update(playerPosition);
    global.camera->update(global.pyddelov->getComponent<TransformComponent>().position);
}

void render()
{
    SDL_RenderClear(global.renderer);

    for (auto& o : global.entityManager.getGroup(0)) {
        o->render();
    }

    for (auto& o : global.entityManager.getGroup(1)) {
        o->render();
    }

    SDL_RenderPresent(global.renderer);
}

int main()
{
    const int fps = 60;
    const int frameDelay = 1000 / fps;

    Uint32 frameStart;
    int frameTime;

    init("Pyddelovs Quest", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 1280, false);

    while (!SDL_QuitRequested()) {
        frameStart = SDL_GetTicks();

        update();
        render();

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