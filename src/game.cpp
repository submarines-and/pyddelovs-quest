#include "game.h"
#include "texture-manager.h"
#include "ecs/ecs.h"
#include "ecs/transform-component.h"
#include "ecs/sprite-component.h"
#include "ecs/keyboard-component.h"
#include "ecs/collision-component.h"
#include "ecs/tile-component.h"

#include "map.h"
#include "vector2d.h"
#include "collision.h"

Manager manager;
SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

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
    for (int i = Map::tiles.size() / 4; i < Map::tiles.size(); i++) {
        if (placed) {
            break;
        }

        auto tile = Map::tiles[i];
        if (tile.typeId == TileComponent::GRASS) {
            player.addComponent<TransformComponent>(tile.x, tile.y);
            placed = true;
        }
    }

    player.addComponent<SpriteComponent>("assets/pyddelov.png");
    player.addComponent<KeyboardComponent>();
    player.addComponent<CollisionComponent>("player");
    player.addGroup(PLAYER);
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
    auto playerCollision = player.getComponent<CollisionComponent>();

    for (auto c : colliders) {

        // cant collide with itself
        if (playerCollision.tag == c->tag) {
            continue;
        }

        if (Collision::isColliding(playerCollision, *c)) {
            player.getComponent<TransformComponent>().velocity * -1;
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
