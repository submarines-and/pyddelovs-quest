#pragma once
#include "../ecs.h"
#include "../game.h"
#include "transform-component.h"
#include "sprite-component.h"

class KeyboardComponent : public Component {
public:
    TransformComponent* transform;
    SpriteComponent* sprite;

    void init() override
    {
        transform = &entity->getComponent<TransformComponent>();
        sprite = &entity->getComponent<SpriteComponent>();
    }

    /** Check for keypress */
    void update() override
    {
        if (Game::event.type == SDL_KEYDOWN) {
            switch (Game::event.key.keysym.sym) {
            case SDLK_w:
            case SDLK_UP:
                transform->velocity.y = -1;
                sprite->spriteFlipped = SDL_FLIP_VERTICAL;
                sprite->playAnimation("Walk");
                break;

            case SDLK_s:
            case SDLK_DOWN:
                transform->velocity.y = 1;
                sprite->playAnimation("Walk");
                break;

            case SDLK_a:
            case SDLK_LEFT:
                transform->velocity.x = -1;
                sprite->spriteFlipped = SDL_FLIP_HORIZONTAL;
                sprite->playAnimation("Walk");
                break;

            case SDLK_d:
            case SDLK_RIGHT:
                transform->velocity.x = 1;
                sprite->playAnimation("Walk");
                break;

            default:
                break;
            }
        }

        if (Game::event.type == SDL_KEYUP) {
            switch (Game::event.key.keysym.sym) {
            case SDLK_w:
            case SDLK_UP:
            case SDLK_s:
            case SDLK_DOWN:
                transform->velocity.y = 0;
                sprite->spriteFlipped = SDL_FLIP_NONE;
                sprite->playAnimation("Idle");
                break;

            case SDLK_a:
            case SDLK_LEFT:

            case SDLK_d:
            case SDLK_RIGHT:
                transform->velocity.x = 0;
                sprite->spriteFlipped = SDL_FLIP_NONE;
                sprite->playAnimation("Idle");
                break;

            default:
                break;
            }
        }
    }
};