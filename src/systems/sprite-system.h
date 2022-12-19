#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <map>

#include "components/sprite.h"
#include "components/transform.h"

#include "ecs/system.h"
#include "global.h"

class SpriteSystem : public System {
private:
    std::map<const char*, SDL_Texture*> textures;

public:
    void update()
    {
        SDL_RenderClear(global.renderer);

        for (auto e : entities) {
            auto& sprite = global.ecs->getComponent<Sprite>(e);
            auto& transform = global.ecs->getComponent<Transform>(e);

            // get sprite
            // load if missing
            SDL_Texture* texture;
            if (sprite.texture) {
                texture = sprite.texture;
            }
            else if (textures.count(sprite.filepath)) {
                texture = textures[sprite.filepath];
            }
            else {
                auto* surface = IMG_Load(sprite.filepath);
                texture = SDL_CreateTextureFromSurface(global.renderer, surface);
                SDL_FreeSurface(surface);
                textures.emplace(sprite.filepath, texture);
            }

            SDL_Rect dest{
                .w = transform.width,
                .h = transform.height,
                .x = (int)transform.position.x,
                .y = (int)transform.position.y,
            };

            // apply animation
            if (sprite.frames > 0) {
                sprite.src.x = sprite.src.w * static_cast<int>((SDL_GetTicks() / 100) % sprite.frames);
                sprite.src.y = sprite.animationIndex * transform.height;
            }

            SDL_RenderCopyEx(global.renderer, texture, &sprite.src, &dest, 0, NULL, sprite.flip);
        }

        SDL_RenderPresent(global.renderer);
    }
};