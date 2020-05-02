#include "audio.h"
#include "leftside_logic.h"
#include "raylib.h"
Music conveyor_sound;
void init_audio()
{
    //Wave wave = LoadWave("assets/audio/conveyor/conveyorsoftermp344100.mp3");
    conveyor_sound = LoadMusicStream("assets/audio/conveyor/conveyorsoftermp344100.mp3");
    SetMusicVolume(conveyor_sound, .05f);
    PlayMusicStream(conveyor_sound);
    //UnloadWave(wave);
}
void update_audio()
{
    if (is_time_up())
    {
        StopMusicStream(conveyor_sound);
    }
    if (GetMouseX() < LEFT_WIDTH)
    {
        SetMusicVolume(conveyor_sound, .25f);
    }
    else
    {
        SetMusicVolume(conveyor_sound, .05f);
    }

    UpdateMusicStream(conveyor_sound);
}
void unload_audio()
{
    UnloadMusicStream(conveyor_sound);
}