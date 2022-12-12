#include "game.h"
#include "ecs/components.h"
#include "ecs/ecs.h"
#include "map.h"
#include "texture-manager.h"

Map* map;
SDL_Renderer* Game::renderer = nullptr;

Manager manager;
auto& player(manager.addEntity());

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

  // give access to pos variables
  player.addComponent<TransformComponent>(100, 500);
  player.addComponent<SpriteComponent>("assets/pyddelov.png");
}

void Game::handleEvents() {
  SDL_Event event;
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
