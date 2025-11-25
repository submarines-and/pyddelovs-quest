#pragma once
#include <SDL2/SDL.h>
#include "util/camera.h"
#include "util/sound.h"
#include "managers/entity-manager.h"
#include "managers/texture-manager.h"

/** All globally available objects */
struct Global {
    SDL_Window* window;
    SDL_Renderer* renderer;

    Camera* camera;

    EntityManager entityManager;
    SoundManager soundManager;
    TextureManager textureManager;
};

/** Will be created by main.cpp */
extern Global& global;