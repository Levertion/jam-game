#include "leftside_graphics.h"
#include "leftside_logic.h"
#include "raylib.h"
#include "shapes.h"
extern Shape AllShapes[3];
void draw_leftside()
{
    ClearBackground(GRAY);

    for (int i = 0; i < items_conveyor.length; i++)
    {
        if (RING_INDEX_POS(items_conveyor, i).y >= 0)
        {
            DrawTexture(AllShapes[RING_INDEX_IDS(items_conveyor, i)].art,
                        RING_INDEX_POS(items_conveyor, i).x, RING_INDEX_POS(items_conveyor, i).y, WHITE);
        }
    }
}