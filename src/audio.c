#include "audio.h"
#include "leftside_logic.h"
#include "raylib.h"
Music main_music;
Music panic_music;

#define NO_VOCALS (10)
#define NO_YEETS (3)

Sound yeet_vocals[NO_VOCALS];
Sound yeets[NO_YEETS];
bool panicing = false;

void init_audio()
{
    yeets[0] = LoadSound("assets/audio/yeet/AltYeet.mp3");
    yeets[1] = LoadSound("assets/audio/yeet/SwishYeet.mp3");
    yeets[2] = LoadSound("assets/audio/yeet/yeetChillPannedBetter.mp3");
    yeet_vocals[0] = LoadSound("assets/audio/yeet/yeetVOcal/yeetvocal.mp3");
    yeet_vocals[1] = LoadSound("assets/audio/yeet/yeetVOcal/yeetVocalFINAL[2high].mp3");
    yeet_vocals[2] = LoadSound("assets/audio/yeet/yeetVOcal/yeetVocalFINAL[2low].mp3");
    yeet_vocals[3] = LoadSound("assets/audio/yeet/yeetVOcal/yeetVocalFINAL[3high].mp3");
    yeet_vocals[4] = LoadSound("assets/audio/yeet/yeetVOcal/yeetVocalFINAL[3low].mp3");
    yeet_vocals[5] = LoadSound("assets/audio/yeet/yeetVOcal/yeetVocalFINAL[5high].mp3");
    yeet_vocals[6] = LoadSound("assets/audio/yeet/yeetVOcal/yeetVocalFINAL[5low].mp3");
    yeet_vocals[7] = LoadSound("assets/audio/yeet/yeetVOcal/yeetVocalFINAL[b7high].mp3");
    yeet_vocals[8] = LoadSound("assets/audio/yeet/yeetVOcal/yeetVocalFINAL[b7low].mp3");
    yeet_vocals[9] = LoadSound("assets/audio/yeet/yeetVOcal/yeetVocalFINAL[R].mp3");

    for (int i = 0; i < NO_VOCALS; i++)
    {
        SetSoundVolume(yeet_vocals[i], 0.2f);
    }
    for (int i = 0; i < NO_YEETS; i++)
    {
        SetSoundVolume(yeets[i], 0.2f);
    }

    //Wave wave = LoadWave("assets/audio/conveyor/conveyorsoftermp344100.mp3");
    main_music = LoadMusicStream("assets/audio/MainLoop.mp3");
    SetMusicVolume(main_music, .1f);
    PlayMusicStream(main_music);
    panic_music = LoadMusicStream("assets/audio/PackingSong.mp3");
    SetMusicVolume(panic_music, .1f);
    //UnloadWave(wave);
}

static int yeet_from_size(int size)
{
    int yeetIdx;
    if (size < 10)
    {
        yeetIdx = 0;
    }
    else if (size < 30)
    {
        yeetIdx = 1;
    }
    else
    {
        yeetIdx = 2;
    }
    int jiggle = GetRandomValue(-1, 1);
    yeetIdx = yeetIdx + jiggle;

    if (yeetIdx < 0)
    {
        return 0;
    }
    else if (yeetIdx >= NO_YEETS)
    {
        return NO_YEETS - 1;
    }
    return yeetIdx;
}

void play_yeet(int size)
{
    int vocal = GetRandomValue(0, NO_VOCALS - 1);
    int yeet = yeet_from_size(size);
    // PlaySoundMulti(yeets[yeet]);
    // PlaySoundMulti(yeet_vocals[vocal]);
}

void update_audio()
{

    if (is_time_up())
    {
        if (!panicing)
        {
            StopMusicStream(main_music);
            PlayMusicStream(panic_music);
        }
        UpdateMusicStream(panic_music);
    }
    else
    {
        UpdateMusicStream(main_music);
    }
    // if (GetMouseX() < LEFT_WIDTH)
    // {
    //     SetMusicVolume(main_music, .15f);
    // }
    // else
    // {
    //     SetMusicVolume(main_music, .1f);
    // }
}
void unload_audio()
{
    StopSoundMulti();
    for (int i = 0; i < NO_VOCALS; i++)
    {
        UnloadSound(yeet_vocals[i]);
    }
    for (int i = 0; i < NO_YEETS; i++)
    {
        UnloadSound(yeets[i]);
    }
    UnloadMusicStream(main_music);
}
