#include "timer.h"
#include "raylib.h"
#include "constants.h"
static double start_time = -1;
static double curr_time;
static const Vector2 timer_location = {10 + LEFT_WIDTH + (SCREEN_WIDTH - LEFT_WIDTH) / 2 - 100, 60};
void start_timer()
{
    if (start_time == -1)
        start_time = GetTime();
    curr_time = GetTime();
}
void draw_timer()
{
    if (is_fun_no_longer_allowed())
        DrawText(TextFormat("%.2lf", 0.0), timer_location.x, timer_location.y, 100, RED);
    else
        DrawText(TextFormat("%.2lf", TIME_LIMIT_TROLLEY - (curr_time - start_time)), timer_location.x, timer_location.y, 50 + 50 * (curr_time - start_time) / TIME_LIMIT_TROLLEY, RED);
}
bool is_fun_no_longer_allowed()
{
    if (start_time == -1)
        return false;
    return (TIME_LIMIT_TROLLEY <= (curr_time - start_time));
}