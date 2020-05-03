#include "draw_trolley.h"

#include "constants.h"
#include "raylib.h"

void DrawTrolley(const TrolleyState *state)
{
    for (int i = 0; i < state->len; i++)
    {
        Item this_item = state->items[i];
        Vector2 render_pos = {
            TROLLEY_X + (float)this_item.posX * GRID_BLOCK_LENGTH + ((this_item.rotation == RotRight || this_item.rotation == RotDown) ? (this_item.shape->art.width) : 0),
            TROLLEY_Y + (float)this_item.posY * GRID_BLOCK_LENGTH + ((this_item.rotation == RotDown || this_item.rotation == RotLeft) ? (this_item.shape->art.height) : 0)};
        float rotation_degrees = 90.f * (float)this_item.rotation;
        Color tint = WHITE;
        // Set image
        // tint.a = 200;
        DrawTextureEx(this_item.shape->art, render_pos, rotation_degrees, 1.0f, tint);
    }
};

void DrawTrolleyGrid()
{
    for (int i = 0; i < TROLLEY_WIDTH; i++)
    {
        for (int j = 0; j < TROLLEY_HEIGHT; j++)
        {
            DrawRectangleLines((int)TROLLEY_X + i * GRID_BLOCK_LENGTH,
                               (int)TROLLEY_Y + j * GRID_BLOCK_LENGTH,
                               GRID_BLOCK_LENGTH, GRID_BLOCK_LENGTH, BLACK);
        }
    }

    //Draw grid for draggable area above trolley
    for (int i = 0; i < TROLLEY_WIDTH; i++)
    {
        for (int j = -BLOCKS_ABOVE_TROLLEY; j < 0; j++)
        {
            Color c = LIGHTGRAY;
            c.a = 100;
            DrawRectangleLines(TROLLEY_X + i * GRID_BLOCK_LENGTH,
                               TROLLEY_Y + j * GRID_BLOCK_LENGTH, GRID_BLOCK_LENGTH, GRID_BLOCK_LENGTH, c);
        }
    }
}