#include "global.h"
#include "gfx/texture-manager.h"
#include "components/transform-component.h"
#include "components/sprite-component.h"
#include "components/keyboard-component.h"
#include "components/collision-component.h"
#include "components/tile-component.h"
#include "level/map.h"
#include "util/vector2d.h"
#include "util/camera.h"
#include "util/entity-manager.h"

/** Init global state and make accessible for main function. */
static Global global_instance;
Global &global = global_instance;

std::vector<CollisionComponent*> colliders;
auto& player(global.manager.addEntity());

enum GroupLabel {
    TERRAIN,
    PLAYER,
    ENEMY
};


void init(const char* title, int x, int y, int width, int height, bool fullscreen)
{
    printf("Starting SDL...\n");

    int flags = 0;
    if (fullscreen) {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        global.window = SDL_CreateWindow(title, x, y, width, height, flags);
        global.renderer = SDL_CreateRenderer(global.window, -1, 0);

        SDL_SetRenderDrawColor(global.renderer, 255, 255, 255, 255);
    }

    // set initial camera position
    global.camera = new Camera(width, height);

    printf("Generating map...\n");
    Map::generate(width, height);

    printf("Placing tiles...\n");
    for (auto t : Map::tiles) {

        auto& tile(global.manager.addEntity());
        tile.addComponent<TileComponent>(t.x, t.y, 32, 32, t.typeId);
        tile.addGroup(TERRAIN);

        switch (t.typeId) {
        case TileComponent::ROCK:
        case TileComponent::WATER:
            tile.addComponent<CollisionComponent>();
            break;

        default:
            break;
        }
    }

    // place player in passabel terrain
    printf("Add player...");
    for (int i = Map::tiles.size() / 2; i < Map::tiles.size(); i++) {
        auto tile = Map::tiles[i];

        // place on the first found grass tile
        if (tile.typeId == TileComponent::GRASS) {
            player.addComponent<TransformComponent>(tile.x, tile.y);
            player.addComponent<SpriteComponent>("assets/pyddelov.png", 4, 100);
            player.addComponent<KeyboardComponent>();
            player.addComponent<CollisionComponent>("player");
            player.addGroup(PLAYER);
            break;
        }
    }

    // start music
    global.soundManager.playMusic("sound/music/forest.mp3");
}

void update()
{
    // position before updates
    auto playerTransform = player.getComponent<TransformComponent>();

    global.manager.refresh();
    global.manager.update();
    global.camera->update(player.getComponent<TransformComponent>().position);

    // bounce on collision
    if (player.hasComponent<CollisionComponent>()) {
        auto playerCollision = player.getComponent<CollisionComponent>();

        for (auto c : colliders) {

            // player cant collide with self
            if (playerCollision.tag == c->tag) {
                continue;
            }

            if (SDL_HasIntersection(&playerCollision.collider, &c->collider)) {
                //     global.soundManager.playSoundEffect("sound/character/bounce.wav");
                player.getComponent<TransformComponent>().position = playerTransform.position;
                break;
            }
        }
    }
}

void render()
{
    SDL_RenderClear(global.renderer);

    for (auto& o : global.manager.getGroup(TERRAIN)) {
        o->render();
    }

    for (auto& o : global.manager.getGroup(PLAYER)) {
        o->render();
    }

    SDL_RenderPresent(global.renderer);
}

void clean()
{
    SDL_DestroyWindow(global.window);
    SDL_DestroyRenderer(global.renderer);
    SDL_Quit();
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

    clean();

    return 0;
}