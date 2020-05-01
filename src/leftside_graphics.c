#include "leftside_graphics.h"
#include "leftside_logic.h"
#include "raylib.h"
#include "shapes.h"
#include <stddef.h>
//#define DEBUG_L1
void draw_leftside()
{
    ClearBackground(GRAY);

    for (int i = 0; i < items_conveyor.length; i++)
    {
#ifdef DEBUG_L1
        DrawText(TextFormat("S: %i L: %i", items_conveyor.start, items_conveyor.length), 0, 0, 20, BLACK);
#endif
        if (items_conveyor.active[RING_INDEX_RAW(items_conveyor, i)])
        {
            DrawTexture(RING_INDEX_IDS(items_conveyor, i)->art,
                        RING_INDEX_POS(items_conveyor, i).x, RING_INDEX_POS(items_conveyor, i).y, WHITE);
        }
        if (current_hold_item.shape != NULL)
        {
            DrawTexture(current_hold_item.shape->art, 0, 0, WHITE);
        }
    }
}