#pragma once
#include <SDL2/SDL.h>
#include <map>
#include "transform-component.h"
#include "gfx/animation.h"
#include "character/entity.h"

class SpriteComponent : public Component {
private:
    TransformComponent* transform;
    SDL_Texture* texture;
    SDL_Rect srcRect, destRect;
    bool animated = false;

public:
    int animationIndex = 0;
    int frames = 0;
    int animationSpeed = 100;
    SDL_RendererFlip spriteFlipped = SDL_FLIP_NONE;
    std::map<const char*, Animation> animations;

    SpriteComponent() = default;
    SpriteComponent(const char* filepath);
    SpriteComponent(const char* filepath, int mFrames, int mSpeed);
    ~SpriteComponent();

    void init() override;
    void update() override;
    void render() override;

    void playAnimation(const char* animationName);
};