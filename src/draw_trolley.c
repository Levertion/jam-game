#include "draw_trolley.h"

#include "constants.h"
#include "raylib.h"

Vector2 GetTrolleyPos()
{
    return (Vector2){889, 360};
}

void DrawTrolley(const TrolleyState *state)
{
    for (int i = 0; i < state->len; i++)
    {
        Item this_item = state->items[i];
        Vector2 render_pos = {
            GetTrolleyPos().x + (float)this_item.posX * GRID_BLOCK_LENGTH + ((this_item.rotation == right || this_item.rotation == down) ? (this_item.shape->art.width) : 0),
            GetTrolleyPos().y + (float)this_item.posY * GRID_BLOCK_LENGTH + ((this_item.rotation == down || this_item.rotation == left) ? (this_item.shape->art.height) : 0)};
        float rotation_degrees = 90.f * (float)this_item.rotation;
        Color test = WHITE;
        // Set image
        test.a = 200;
        DrawTextureEx(this_item.shape->art, render_pos, rotation_degrees, 1.0f, test);
    }
};

void DrawTrolleyGrid()
{
    for (int i = 0; i < TROLLEY_WIDTH; i++)
    {
        for (int j = 0; j < TROLLEY_HEIGHT; j++)
        {
            DrawRectangleLines((int)GetTrolleyPos().x + i * GRID_BLOCK_LENGTH,
                               (int)GetTrolleyPos().y + j * GRID_BLOCK_LENGTH,
                               GRID_BLOCK_LENGTH, GRID_BLOCK_LENGTH, BLACK);
        }
    }
}