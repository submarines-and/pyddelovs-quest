#pragma once
#include <SDL2/SDL.h>
#include "util/camera.h"
#include "util/sound.h"
#include "character/entity.h"
#include "util/level.h"
#include "gfx/textures.h"

/** All globally available objects */
struct Global {
    SDL_Window* window;
    SDL_Renderer* renderer;

    Camera* camera;

    EntityManager entityManager;
    Level level;
    SoundManager soundManager;
    Textures textures;
};

/** Will be created by main.cpp */
extern Global& global;