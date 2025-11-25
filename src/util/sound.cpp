#include "sound.h"

SoundManager::SoundManager()
{
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
}

SoundManager::~SoundManager()
{
    Mix_HaltMusic();
    Mix_FreeMusic(music);

    for (auto s : sounds) {
        Mix_FreeChunk(s.second);
    }

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

/** Plays a sound effect*/
void SoundManager::playSoundEffect(const char* filepath)
{
    Mix_Chunk* sound;

    // check cache - load if missing
    if (sounds.count(filepath)) {
        sound = sounds[filepath];
    }
    else {
        sound = Mix_LoadWAV(filepath);

        if (sound == NULL) {
            printf("SDL_mixer Error: %s\n", Mix_GetError());
            return;
        }

        sounds.emplace(filepath, sound);
    }

    // play
    Mix_PlayChannel(-1, sound, 0);
}
