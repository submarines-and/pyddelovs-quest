#include "sound.h"

Sound::Sound()
{
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
}

Sound::~Sound()
{
    Mix_HaltMusic();
    Mix_FreeMusic(music);

    for (auto s : sounds) {
        Mix_FreeChunk(s.second);
    }

    Mix_Quit();
}

/** Play music at given filepath */
void Sound::playMusic(const char* filepath)
{
    if (Mix_PlayingMusic() != 0) {
        return;
    }

    music = Mix_LoadMUS(filepath);
    Mix_PlayMusic(music, -1);
}

/** Plays a sound effect*/
void Sound::playSoundEffect(const char* filepath)
{
    Mix_Chunk* sound;

    // check cache - load if missing
    if (sounds.count(filepath)) {
        sound = sounds[filepath];
    }
    else {
        sound = Mix_LoadWAV(filepath);
        sounds.emplace(filepath, sound);
    }

    if (sound == NULL) {
        printf("Sound not found %s %s\n", filepath, Mix_GetError());
        return;
    }

    // play
    Mix_PlayChannel(-1, sound, 0);
}
