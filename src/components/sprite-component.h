#pragma once
#include "SDL2/SDL.h"
#include <map>
#include "managers/entity-manager.h"
#include "transform-component.h"
#include "animation-component.h"
#include "global.h"

class SpriteComponent : public Component {
private:
    TransformComponent* transform;
    SDL_Texture* texture;
    SDL_Rect srcRect, destRect;

    /** Set to true if sprite is animated */
    bool animated = false;

public:
    int animationIndex = 0;
    int frames = 0;
    int animationSpeed = 100;

    /** If sprite is flipped */
    SDL_RendererFlip spriteFlipped = SDL_FLIP_NONE;

    std::map<const char*, Animation> animations;

    SpriteComponent() = default;

    SpriteComponent(const char* filepath)
    {
        setTexture(filepath);
    }

    SpriteComponent(const char* filepath, int mFrames, int mSpeed)
    {
        animated = true;
        auto idle = Animation(0, mFrames, mSpeed);

        // same file for now
        animations.emplace("Idle", idle);
        animations.emplace("Walk", idle);

        setTexture(filepath);

        // default animation
        playAnimation("Idle");
    }

    ~SpriteComponent()
    {
        SDL_DestroyTexture(texture);
    }

    void setTexture(const char* filepath)
    {
        texture = global.textureManager.loadTexture(filepath);
    }

    void init() override
    {
        transform = &entity->getComponent<TransformComponent>();

        srcRect.x = srcRect.y = 0;
        srcRect.w = transform->width;
        srcRect.h = transform->height;
    }

    void update() override
    {
        if (animated) {
            srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / animationSpeed) % frames);
            srcRect.y = animationIndex * transform->height;
        }

        destRect.x = static_cast<int>(transform->position.x) - global.camera->position.x;
        destRect.y = static_cast<int>(transform->position.y) - global.camera->position.y;

        destRect.w = transform->width;
        destRect.h = transform->height;
    }

    void render() override
    {
        global.textureManager.render(texture, srcRect, destRect, spriteFlipped);
    }

    void playAnimation(const char* animationName)
    {
        animationIndex = animations[animationName].index;
        frames = animations[animationName].frames;
        animationSpeed = animations[animationName].animationSpeed;
    }
};