#include "leftside_logic.h"
#include "raylib.h"
#include "shapes.h"
#define LS_LOGICAL_HEIGHT (900)
#define LS_LOGICAL_WIDTH (600)
static const int conveyor_velocity = 5;
static int deploy_cooldown = 0;

static void reroll_item(int i)
{
    items_conveyor.shapes[i] = GetRandomShape();
    items_conveyor.positions[i].x = (float)GetRandomValue(0, LS_LOGICAL_WIDTH - items_conveyor.shapes[i]->art.width);
    items_conveyor.positions[i].y = (float)-items_conveyor.shapes[i]->art.height - deploy_cooldown * conveyor_velocity;
    deploy_cooldown += items_conveyor.shapes[i]->art.height / conveyor_velocity;
    items_conveyor.active[i] = 1;
}

void leftside_init()
{
    items_conveyor.start = 0;
    items_conveyor.length = 0;
}
void leftside_logic()
{
    //generate shapes if required
    if (deploy_cooldown > 0)
    {
        deploy_cooldown--;
    }
    else if (items_conveyor.length < MAX_BUFFER_SIZE_ITEMS)
    {

        reroll_item(items_conveyor.length);

        items_conveyor.length++;
    }

    //cull out of bounds
    while (RING_INDEX_POS(items_conveyor, 0).y > LS_LOGICAL_HEIGHT + RING_INDEX_IDS(items_conveyor, 0)->art.height)
    {
        //reroll image
        reroll_item(RING_INDEX_RAW(items_conveyor, 0));

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
        if (items_conveyor.active[RING_INDEX_RAW(items_conveyor, i)] && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && GetMouseX() >= RING_INDEX_POS(items_conveyor, i).x && GetMouseX() <= RING_INDEX_POS(items_conveyor, i).x + RING_INDEX_IDS(items_conveyor, i)->art.width && GetMouseY() >= RING_INDEX_POS(items_conveyor, i).y && GetMouseY() <= RING_INDEX_POS(items_conveyor, i).y + RING_INDEX_IDS(items_conveyor, i)->art.height)
        {
            mouse_block_x = (int)(GetMouseX() - RING_INDEX_POS(items_conveyor, i).x) / (RING_INDEX_IDS(items_conveyor, i)->art.width / 8);
            mouse_block_y = (int)(GetMouseY() - RING_INDEX_POS(items_conveyor, i).y) / (RING_INDEX_IDS(items_conveyor, i)->art.height / 8);
            if (RING_INDEX_IDS(items_conveyor, i)->grid[mouse_block_y][mouse_block_x] == 1)
            {
                current_hold_item.shape = RING_INDEX_IDS(items_conveyor, i);
                items_conveyor.active[RING_INDEX_RAW(items_conveyor, i)] = 0;
                break;
            }
        }
    }

    for (int i = 0; i < items_conveyor.length; i++)
    {
        RING_INDEX_POS(items_conveyor, i).y += conveyor_velocity;
    }
}