#pragma once
#include <SDL2/SDL.h>
#include <map>

#include "components/transform.h"
#include "components/player.h"
#include "ecs/system.h"
#include "util/vector2d.h"
#include "global.h"

class TransformSystem : public System {
private:
    SDL_Rect windowSize;
    SDL_Rect cameraPosition;

public:
    void init(int width, int height)
    {
        windowSize = {0, 0, width, height};
        cameraPosition = {0, 0, width, height};
    }

    void update(Vector2d playerPosition, float deltaTime)
    {
        cameraPosition.x = playerPosition.x - windowSize.w / 2;
        cameraPosition.y = playerPosition.y - windowSize.h / 2;

        // check bounds
        if (cameraPosition.x < 0) {
            // cameraPosition.x = 0;
        }
        if (cameraPosition.y < 0) {
            // cameraPosition.y = 0;
        }
        if (cameraPosition.x > cameraPosition.w) {
            // cameraPosition.x = cameraPosition.w;
        }
        if (cameraPosition.y > cameraPosition.h) {
            // cameraPosition.y = cameraPosition.h;
        }

        for (auto e : entities) {
            auto& transform = global.ecs->getComponent<Transform>(e);

            transform.position.x += transform.direction.x * transform.speed * deltaTime - cameraPosition.x;
            transform.position.y += transform.direction.y * transform.speed * deltaTime - cameraPosition.y;
        }
    }
};