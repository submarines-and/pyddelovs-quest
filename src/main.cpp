#include "game.h"

int main()
{
  Game *game = new Game();
  game->init("Krabban klo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);

  while (game->running())
  {
    game->handleEvents();
    game->update();
    game->render();
  }

  game->clean();

  return 0;
}
