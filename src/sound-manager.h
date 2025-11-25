#pragma once
#include <SDL2/SDL_mixer.h>

class SoundManager {

private:
    Mix_Music* music = NULL;

public:
    SoundManager();
    ~SoundManager();
    void playMusic(const char* filepath);
};