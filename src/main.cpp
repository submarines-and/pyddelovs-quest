#include "game.h"

int main()
{
  const int fps = 60;
  const int frameDelay = 1000 / fps;

  Uint32 frameStart;
  int frameTime;

  Game *game = new Game();
  game->init("Pyddelovs Quest", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, false);

  while (game->running())
  {
    frameStart = SDL_GetTicks();

    game->handleEvents();
    game->update();
    game->render();

    frameTime = SDL_GetTicks() - frameStart;

    if (frameDelay > frameTime)
    {
      SDL_Delay(frameDelay - frameTime);
    }
  }

  game->clean();

  return 0;
}
