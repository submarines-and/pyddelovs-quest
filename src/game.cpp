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

    player.addComponent<TransformComponent>(100.0f, 100.0f);
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

void Game::addTile(int id, int x, int y)
{
    auto& tile(manager.addEntity());
    tile.addComponent<TileComponent>(x, y, 32, 32, id);
    tile.addGroup(TERRAIN);

    switch (id) {
    case TileComponent::ROCK:
    case TileComponent::WATER:
        tile.addComponent<CollisionComponent>();
        break;

    default:
        break;
    }
}
