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

    EntityManager entityManager;
    Camera* camera;
    Level level;
    Sound sound;
    Textures textures;

    Entity* pyddelov;
};

/** Will be created by main.cpp */
extern Global& global;