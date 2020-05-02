#include "leftside_graphics.h"
#include "leftside_logic.h"
#include "raylib.h"
#include "shapes.h"
#include <stddef.h>
//#define DEBUG_L1
static Shape *yeetable = NULL;
static int yeet_location = -240, yeet_rotation = 0, yeet_y = 200;
static int yeet_velocity = 20, yeet_angular_velocity = 15;
void yeet_shape(Shape *shape)
{
    yeetable = shape;
    yeet_rotation = 0;
    yeet_location = LS_LOGICAL_WIDTH + shape->art.width;
}
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
        if (yeetable != NULL)
        {
            if (yeet_location > -yeetable->art.width)
            {
                Vector2 origin = {yeetable->art.width / 2, yeetable->art.height / 2};
                Rectangle src = {0, 0, yeetable->art.width, yeetable->art.height};
                Rectangle dest = {yeet_location, yeet_y, yeetable->art.width, yeetable->art.height};
                DrawTexturePro(yeetable->art, src, dest, origin, yeet_rotation, WHITE);
                yeet_rotation += yeet_angular_velocity;
                yeet_location -= yeet_velocity;
            }
        }
        if (current_hold_item_L.shape != NULL)
        {
            DrawTexture(current_hold_item_L.shape->art, 0, 0, WHITE);
        }
    }
}