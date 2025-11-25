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

Map* map;
Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

std::vector<CollisionComponent*> Game::colliders;

auto& player(manager.addEntity());

auto& waterTile(manager.addEntity());
auto& dirtTile(manager.addEntity());

Game::Game() {
}

Game::~Game() {
}

void Game::init(const char* title, int x, int y, int width, int height, bool fullscreen) {
    int flags = 0;
    if (fullscreen) {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        window = SDL_CreateWindow(title, x, y, width, height, flags);
        renderer = SDL_CreateRenderer(window, -1, 0);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        isRunning = true;
    } else {
        isRunning = false;
    }

    // starting map?
    map = new Map();

    dirtTile.addComponent<TileComponent>(250, 250, 32, 32, TileComponent::DIRT);
    waterTile.addComponent<TileComponent>(200, 200, 32, 32, TileComponent::WATER);
    waterTile.addComponent<CollisionComponent>();

    player.addComponent<TransformComponent>(100.0f, 100.0f);
    player.addComponent<SpriteComponent>("assets/pyddelov.png");
    player.addComponent<KeyboardComponent>();
    player.addComponent<CollisionComponent>("player");
}

void Game::handleEvents() {
    SDL_PollEvent(&event);

    switch (event.type) {
    case SDL_QUIT:
        isRunning = false;
        break;

    default:
        break;
    }
}

void Game::update() {
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

void Game::render() {
    SDL_RenderClear(renderer);
    map->render();
    manager.render();
    SDL_RenderPresent(renderer);
}

void Game::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}
