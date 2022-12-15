#include "sprite-component.h"
#include "global.h"

SpriteComponent::SpriteComponent(const char* filepath)
{
    texture = global.textureManager.loadTexture(filepath);
}

SpriteComponent::SpriteComponent(const char* filepath, int mFrames, int mSpeed)
{
    animated = true;
    auto idle = Animation(0, mFrames, mSpeed);

    // same file for now
    animations.emplace("Idle", idle);
    animations.emplace("Walk", idle);

    texture = global.textureManager.loadTexture(filepath);

    // play default animation
    playAnimation("Idle");
}

SpriteComponent::~SpriteComponent()
{
    SDL_DestroyTexture(texture);
}

void SpriteComponent::init()
{
    transform = &entity->getComponent<TransformComponent>();

    srcRect.x = srcRect.y = 0;
    srcRect.w = transform->width;
    srcRect.h = transform->height;
}

void SpriteComponent::update()
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

void SpriteComponent::render()
{
    global.textureManager.render(texture, srcRect, destRect, spriteFlipped);
}

void SpriteComponent::playAnimation(const char* animationName)
{
    animationIndex = animations[animationName].index;
    frames = animations[animationName].frames;
    animationSpeed = animations[animationName].animationSpeed;
}
