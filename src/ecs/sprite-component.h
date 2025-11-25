#pragma once
#include "SDL2/SDL.h"
#include "components.h"

class SpriteComponent : public Component {
private:
    TransformComponent* transform;
    SDL_Texture* texture;
    SDL_Rect srcRect, destRect;

public:
    SpriteComponent() = default;
    SpriteComponent(const char* filepath) {
        setTexture(filepath);
    }

    void setTexture(const char* filepath) {
        texture = TextureManager::loadTexture(filepath);
    }

    void init() override {
        transform = &entity->getComponent<TransformComponent>();
        srcRect.x = srcRect.y = 0;
        destRect.x = destRect.y = 0;

        srcRect.w = srcRect.h = 32;
        destRect.w = destRect.h = 64;
    }

    void update() override {
        destRect.x = transform->x();
        destRect.y = transform->y();
    }

    void render() override {
        TextureManager::render(texture, srcRect, destRect);
    }
};