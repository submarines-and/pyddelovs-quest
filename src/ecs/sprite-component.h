#pragma once
#include "SDL2/SDL.h"
#include "ecs.h"
#include "transform-component.h"
#include "../texture-manager.h"

class SpriteComponent : public Component {
private:
    TransformComponent* transform;
    SDL_Texture* texture;
    SDL_Rect srcRect, destRect;

    /** Set to true if sprite is animated */
    bool animated = false;
    int frames = 0;

    /** Delay in ms */
    int speed = 100;

public:
    SpriteComponent() = default;

    SpriteComponent(const char* filepath)
    {
        setTexture(filepath);
    }

    SpriteComponent(const char* filepath, int mFrames, int mSpeed)
    {
        animated = true;
        frames = mFrames;
        speed = mSpeed;

        setTexture(filepath);
    }

    ~SpriteComponent()
    {
        SDL_DestroyTexture(texture);
    }

    void setTexture(const char* filepath)
    {
        texture = TextureManager::loadTexture(filepath);
    }

    void init() override
    {
        transform = &entity->getComponent<TransformComponent>();

        srcRect.x = srcRect.y = 0;
        destRect.x = destRect.y = 0;

        srcRect.w = transform->width;
        srcRect.h = transform->height;

        destRect.w = srcRect.w * transform->scale;
        destRect.h = srcRect.h * transform->scale;
    }

    void update() override
    {
        if (animated) {
            srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
        }

        destRect.x = static_cast<int>(transform->position.x);
        destRect.y = static_cast<int>(transform->position.y);

        destRect.w = transform->width * transform->scale;
        destRect.h = transform->height * transform->scale;
    }

    void render() override
    {
        TextureManager::render(texture, srcRect, destRect);
    }
};