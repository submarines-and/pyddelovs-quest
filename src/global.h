#pragma once
#include <SDL2/SDL.h>
#include "util/camera.h"
#include "util/sound-manager.h"
#include "util/entity-manager.h"
#include "gfx/texture-manager.h"

/** All globally available objects */
struct Global {
    SDL_Window* window;
    SDL_Renderer* renderer;

    Camera* camera;

    EntityManager entityManager;
    SoundManager soundManager;
    TextureManager textureManager;
};

extern Global& global;