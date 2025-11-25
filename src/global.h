#pragma once
#include <SDL2/SDL.h>
#include "ecs/ecs.h"
#include "util/sound.h"
#include "util/score.h"

/** All globally available objects */
struct Global {
    SDL_Window* window;
    SDL_Renderer* renderer;

    ECS* ecs;
    Sound* sound;
    Score* score;
};

/** Will be created by main.cpp */
extern Global& global;