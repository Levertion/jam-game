#include "audio.h"
#include "raylib.h"
Sound conveyor_sound;
void init_audio()
{
    Wave wave = LoadWave("assets/audio/conveyor/conveyormp344100.mp3");
    conveyor_sound = LoadSoundFromWave(wave);
    SetSoundVolume(conveyor_sound, .2f);
    UnloadWave(wave);
}
void update_audio()
{
    if (!IsSoundPlaying(conveyor_sound))
        PlaySound(conveyor_sound);
}
void unload_audio()
{
    UnloadSound(conveyor_sound);
}