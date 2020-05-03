#include "timer.h"
#include "raylib.h"
#include "constants.h"
static double start_time = -1;
static double curr_time;
bool finished = false;
static const Vector2 timer_location = {10 + LEFT_WIDTH + (SCREEN_WIDTH - LEFT_WIDTH) / 2 - 100, 60};
static const Rectangle checkout_button_rec = {10 + LEFT_WIDTH + (SCREEN_WIDTH - LEFT_WIDTH) / 2 - 100, 150, 160, 50};
void start_timer()
{
    if (start_time == -1)
        start_time = GetTime();
    if (!game_ended())
    {
        curr_time = GetTime();
    }
}
void draw_checkout_button()
{
    DrawRectangleRec(checkout_button_rec, MAROON);
    if (CheckCollisionPointRec(GetMousePosition(), checkout_button_rec))
        DrawText("CHECKOUT", checkout_button_rec.x + 10, checkout_button_rec.y + 15, checkout_button_rec.height * .5, WHITE);
    else
        DrawText("CHECKOUT", checkout_button_rec.x + 10, checkout_button_rec.y + 15, checkout_button_rec.height * .5, BLACK);
}
bool is_checkout_button_pressed()
{
    return (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), checkout_button_rec));
}
void draw_timer()
{
    if (!finished)
        draw_checkout_button();
    if (start_time == -1 || TIME_LIMIT_TROLLEY - (curr_time - start_time) < 0.0f)
        DrawText(TextFormat("%.2lf", 0.0), timer_location.x, timer_location.y, 100, RED);
    else
        DrawText(TextFormat("%.2lf", TIME_LIMIT_TROLLEY - (curr_time - start_time)), timer_location.x, timer_location.y, 50 + 50 * (curr_time - start_time) / TIME_LIMIT_TROLLEY, RED);
}

bool game_ended()
{
    if (start_time != -1 && TIME_LIMIT_TROLLEY <= (curr_time - start_time))
        finished = true;

    return finished;
}

void finish_game()
{
    finished = true;
}