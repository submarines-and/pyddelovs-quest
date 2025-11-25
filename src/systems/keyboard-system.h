#pragma once
#include <SDL2/SDL.h>

#include "components/transform.h"
#include "components/sprite.h"

#include "entities/void-bolt.h"

#include "ecs/system.h"
#include "global.h"

class KeyboardSystem : public System {
private:
    SDL_Event event;

public:
    void update()
    {
        SDL_PollEvent(&event);

        for (auto e : entities) {
            auto& transform = global.ecs->getComponent<Transform>(e);
            auto& sprite = global.ecs->getComponent<Sprite>(e);

            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                case SDLK_w:
                case SDLK_UP:
                    transform.direction.y = -1;
                    sprite.flip = SDL_FLIP_VERTICAL;
                    break;

                case SDLK_s:
                case SDLK_DOWN:
                    transform.direction.y = 1;
                    break;

                case SDLK_a:
                case SDLK_LEFT:
                    transform.direction.x = -1;
                    sprite.flip = SDL_FLIP_HORIZONTAL;
                    break;

                case SDLK_d:
                case SDLK_RIGHT:
                    transform.direction.x = 1;
                    break;

                case SDLK_SPACE:
                    VoidBolt::create(transform.position.x, transform.position.y);
                    break;

                default:
                    break;
                }
            }

            if (event.type == SDL_KEYUP) {
                switch (event.key.keysym.sym) {
                case SDLK_w:
                case SDLK_UP:
                case SDLK_s:
                case SDLK_DOWN:
                    transform.direction.y = 0;
                    sprite.flip = SDL_FLIP_NONE;
                    break;

                case SDLK_a:
                case SDLK_LEFT:

                case SDLK_d:
                case SDLK_RIGHT:
                    transform.direction.x = 0;
                    sprite.flip = SDL_FLIP_NONE;
                    break;

                default:
                    break;
                }
            }

            transform.direction.normalize();
        }
    }
};