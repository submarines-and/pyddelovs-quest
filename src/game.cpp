#include "game.h"
#include "texture-manager.h"
#include "sound-manager.h"
#include "ecs.h"
#include "components/transform-component.h"
#include "components/sprite-component.h"
#include "components/keyboard-component.h"
#include "components/collision-component.h"
#include "components/tile-component.h"
#include "map.h"
#include "vector2d.h"

Manager manager;
SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
SoundManager soundManager;
Camera Game::camera;

std::vector<CollisionComponent*> Game::colliders;

auto& player(manager.addEntity());

enum GroupLabel {
    TERRAIN,
    PLAYER,
    ENEMY
};
auto& playerGroup(manager.getGroup(PLAYER));
auto& terrainGroup(manager.getGroup(TERRAIN));

Game::Game() {}
Game::~Game() {}

void Game::init(const char* title, int x, int y, int width, int height, bool fullscreen)
{
    printf("Starting SDL...\n");

    int flags = 0;
    if (fullscreen) {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        window = SDL_CreateWindow(title, x, y, width, height, flags);
        renderer = SDL_CreateRenderer(window, -1, 0);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        isRunning = true;
    }
    else {
        isRunning = false;
    }

    // set initial camera position
    camera.setPosition(width, height);

    printf("Generating map...\n");
    Map::generate(width, height);

    printf("Placing tiles...\n");
    for (auto t : Map::tiles) {

        auto& tile(manager.addEntity());
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
    soundManager.playMusic("sound/music/forest.mp3");
}

void Game::handleEvents()
{
    SDL_PollEvent(&event);

    switch (event.type) {
    case SDL_QUIT:
        isRunning = false;
        break;

    default:
        break;
    }
}

void Game::update()
{
    // position before updates
    auto playerTransform = player.getComponent<TransformComponent>();

    manager.refresh();
    manager.update();
    camera.update(player.getComponent<TransformComponent>().position);

    // bounce on collision
    if (player.hasComponent<CollisionComponent>()) {
        auto playerCollision = player.getComponent<CollisionComponent>();

        for (auto c : colliders) {

            // player cant collide with self
            if (playerCollision.tag == c->tag) {
                continue;
            }

            if (SDL_HasIntersection(&playerCollision.collider, &c->collider)) {
                //     soundManager.playSoundEffect("sound/character/bounce.wav");
                player.getComponent<TransformComponent>().position = playerTransform.position;
                break;
            }
        }
    }
}

void Game::render()
{
    SDL_RenderClear(renderer);

    for (auto& o : terrainGroup) {
        o->render();
    }

    for (auto& o : playerGroup) {
        o->render();
    }

    SDL_RenderPresent(renderer);
}

void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}
