#include "draw_cache.h"
#include "leftside_logic.h"
#include "constants.h"
#include <stddef.h>
static const Vector2 loc_L = {10 + LEFT_WIDTH, 10}, loc_R = {SCREEN_WIDTH - 360, 10};

void draw_cache()
{
    DrawText("L:", loc_L.x, loc_L.y + 100, 40, BLACK);
    if (current_hold_item_L.shape != NULL)
    {
        DrawTexture(current_hold_item_L.shape->art, loc_L.x + 40, loc_L.y, WHITE);
    }
    DrawText("R:", loc_R.x, loc_R.y + 100, 40, BLACK);
    if (current_hold_item_R.shape != NULL)
    {
        DrawTexture(current_hold_item_R.shape->art, loc_R.x + 40, loc_R.y, WHITE);
    }
}