#include "audio.h"
#include "raylib.h"
Music conveyor_sound;
void init_audio()
{
    //Wave wave = LoadWave("assets/audio/conveyor/conveyorsoftermp344100.mp3");
    conveyor_sound = LoadMusicStream("assets/audio/conveyor/conveyorsoftermp344100.mp3");
    SetMusicVolume(conveyor_sound, .2f);
    PlayMusicStream(conveyor_sound);
    //UnloadWave(wave);
}
void update_audio()
{
    UpdateMusicStream(conveyor_sound);
}
void unload_audio()
{
    UnloadMusicStream(conveyor_sound);
}