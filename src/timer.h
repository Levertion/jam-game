#ifndef TIMER_GUARD
#define TIMER_GUARD
#define TIME_LIMIT_TROLLEY ((double)180.0f)
#include "raylib.h"
void start_timer();
void draw_timer();
bool game_ended();
void finish_game();
#endif