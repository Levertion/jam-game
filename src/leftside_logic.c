#include "leftside_logic.h"
#include "raylib.h"
#include "shapes.h"
#define LS_LOGICAL_HEIGHT (900)
#define LS_LOGICAL_WIDTH (600)
static const int conveyor_velocity = 5;

void leftside_init()
{
    items_conveyor.start = 0;
    items_conveyor.length = 0;
}
void leftside_logic()
{
    static int deploy_cooldown = 0;
    //generate shapes if required
    if (deploy_cooldown > 0)
    {
        deploy_cooldown--;
    }
    else if (items_conveyor.length < MAX_BUFFER_SIZE_ITEMS)
    {

        items_conveyor.shapes[items_conveyor.length] = GetRandomShape();
        items_conveyor.positions[items_conveyor.length].x = GetRandomValue(0, LS_LOGICAL_WIDTH - items_conveyor.shapes[items_conveyor.length]->art.width);
        items_conveyor.positions[items_conveyor.length].y = -items_conveyor.shapes[items_conveyor.length]->art.height;
        deploy_cooldown = items_conveyor.shapes[items_conveyor.length]->art.height / conveyor_velocity;

        items_conveyor.length++;
    }

    //cull out of bounds
    while (RING_INDEX_POS(items_conveyor, 0).y > LS_LOGICAL_HEIGHT + RING_INDEX_IDS(items_conveyor, 0)->art.height)
    {
        //reroll image
        RING_INDEX_IDS(items_conveyor, 0) = GetRandomShape();
        RING_INDEX_POS(items_conveyor, 0).x = GetRandomValue(0, LS_LOGICAL_WIDTH - RING_INDEX_IDS(items_conveyor, 0)->art.width);
        RING_INDEX_POS(items_conveyor, 0).y = -RING_INDEX_IDS(items_conveyor, 0)->art.height - deploy_cooldown * conveyor_velocity;

        deploy_cooldown += RING_INDEX_IDS(items_conveyor, 0)->art.height / conveyor_velocity;

        //shifts to next position
        items_conveyor.start++;
        if (items_conveyor.start == items_conveyor.length)
        {
            items_conveyor.start = 0;
        }
    }

    //------------------------------------------------
    //Mouse Selection
    //------------------------------------------------
    int mouse_block_x, mouse_block_y;
    for (int i = 0; i < items_conveyor.length; i++)
    {
        //mouse in bounding box
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && GetMouseX() >= RING_INDEX_POS(items_conveyor, i).x && GetMouseX() <= RING_INDEX_POS(items_conveyor, i).x + RING_INDEX_IDS(items_conveyor, i)->art.width && GetMouseY() >= RING_INDEX_POS(items_conveyor, i).y && GetMouseY() <= RING_INDEX_POS(items_conveyor, i).y + RING_INDEX_IDS(items_conveyor, i)->art.height)
        {
            mouse_block_x = (GetMouseX() - RING_INDEX_POS(items_conveyor, i).x) / (RING_INDEX_IDS(items_conveyor, i)->art.width / 8);
            mouse_block_y = (GetMouseY() - RING_INDEX_POS(items_conveyor, i).y) / (RING_INDEX_IDS(items_conveyor, i)->art.height / 8);
            if (RING_INDEX_IDS(items_conveyor, i)->grid[mouse_block_y][mouse_block_x] == 1)
            {
                current_hold_item.shape = RING_INDEX_IDS(items_conveyor, i);
            }
        }
    }

    for (int i = 0; i < items_conveyor.length; i++)
    {
        RING_INDEX_POS(items_conveyor, i).y += conveyor_velocity;
    }
}