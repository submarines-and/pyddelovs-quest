#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>

class CollisionComponent;

class Game {

public:
    Game();
    ~Game();

    void init(const char* title, int x, int y, int width, int height, bool fullscreen);

    void handleEvents();
    void update();
    void render();
    void clean();

    bool running() { return isRunning; }

    /** Global renderer */
    static SDL_Renderer* renderer;
    static SDL_Event event;

    /** Camera is just a rectangle */
    static SDL_Rect camera;

    /** All collidable objects */
    static std::vector<CollisionComponent*> colliders;

private:
    bool isRunning;
    SDL_Window* window;
    static SDL_Rect windowSize;

};