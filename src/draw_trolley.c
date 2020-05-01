#include "draw_trolley.h"

#include "constants.h"
#include "raylib.h"

Vector2 GetTrolleyPos()
{
    Vector2 trolley_pos = {889, 360};
    return trolley_pos;
}

/*void InitialiseTrolley()
{
    //This should help the trolley position adapt to the resolution
    //static Vector2 grid_start_ratio = {0.556f, 0.4f};
    static Vector2 top_left_pos = {(float)SCREEN_WIDTH * grid_start_ratio.x, (float)SCREEN_HEIGHT * grid_start_ratio.y};
}*/

void DrawTrolley(TrolleyState state)
{
    for (int i = 0; i < state.numItems; i++)
    {
        Item this_item = state.items[i];
        Vector2 render_pos = {
            GetTrolleyPos().x + (float)this_item.posX * GRID_BLOCK_LENGTH + (this_item.rotation == right || this_item.rotation == down) ? (this_item.shape->art.height) : 0,
            GetTrolleyPos().y + (float)this_item.posY * GRID_BLOCK_LENGTH + (this_item.rotation == down || this_item.rotation == left) ? (this_item.shape->art.height) : 0};
        float rotation_degrees = 90.f * (float)this_item.rotation;

        DrawTextureEx(this_item.shape->art, render_pos, rotation_degrees, 1.0f, WHITE);
    }
};
