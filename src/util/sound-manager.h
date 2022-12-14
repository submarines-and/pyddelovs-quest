#pragma once
#include <SDL2/SDL_mixer.h>
#include <map>

class SoundManager {

private:
    Mix_Music* music = NULL;
    std::map<const char*, Mix_Chunk*> sounds;

public:
    SoundManager();
    ~SoundManager();
    void playMusic(const char* filepath);
    void playSoundEffect(const char* filepath);
};