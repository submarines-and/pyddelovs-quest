#pragma once
#include <SDL2/SDL.h>
#include "util/camera.h"
#include "util/sound-manager.h"
#include "util/entity-manager.h"

/** All globally available objects */
struct Global {
    SDL_Window* window;
    SDL_Renderer* renderer;

    Camera* camera;
    SoundManager soundManager;
    EntityManager manager;
};

extern Global& global;