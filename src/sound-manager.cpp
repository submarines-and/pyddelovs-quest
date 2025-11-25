#include "sound-manager.h"
// https://lazyfoo.net/tutorials/SDL/21_sound_effects_and_music/index.php

SoundManager::SoundManager()
{
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
}

SoundManager::~SoundManager()
{
    Mix_HaltMusic();
    Mix_FreeMusic(music);
    Mix_Quit();
}

/** Play music at given filepath */
void SoundManager::playMusic(const char* filepath)
{
    if (Mix_PlayingMusic() != 0) {
        return;
    }

    music = Mix_LoadMUS(filepath);
    Mix_PlayMusic(music, -1);
}
