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

std::vector<CollisionComponent*> Game::colliders;

auto& player(manager.addEntity());

enum GroupLabel {
    TERRAIN,
    PLAYER,
    ENEMY
};

Game::Game() {}
Game::~Game() {}

void Game::init(const char* title, int x, int y, int width, int height, bool fullscreen)
{
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

    Map::generate(width, height);
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
    bool placed = false;
    for (int i = Map::tiles.size() / 2; i < Map::tiles.size(); i++) {
        if (placed) {
            break;
        }

        // place on a grass tile
        auto tile = Map::tiles[i];
        if (tile.typeId == TileComponent::GRASS) {
            player.addComponent<TransformComponent>(tile.x, tile.y);
            placed = true;
        }
    }

    if (placed) {
        player.addComponent<SpriteComponent>("assets/pyddelov-ss.png", 4, 100);
        player.addComponent<KeyboardComponent>();
        player.addComponent<CollisionComponent>("player");
        player.addGroup(PLAYER);
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
    manager.refresh();
    manager.update();

    // bounce on collision
    if (player.hasComponent<CollisionComponent>()) {
        auto playerCollision = player.getComponent<CollisionComponent>();

        for (auto c : colliders) {

            // player cant collide with self
            if (playerCollision.tag == c->tag) {
                continue;
            }

            if (SDL_HasIntersection(&playerCollision.collider, &c->collider)) {
                player.getComponent<TransformComponent>().velocity * -1;
                break;
            }
        }
    }
}

auto& terrainGroup(manager.getGroup(TERRAIN));
auto& playerGroup(manager.getGroup(PLAYER));

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
