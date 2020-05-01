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
        RING_INDEX_POS(items_conveyor, items_conveyor.length - 1).y = -items_conveyor.shapes[items_conveyor.length]->art.height;
        deploy_cooldown = items_conveyor.shapes[items_conveyor.length]->art.height / conveyor_velocity;

        items_conveyor.length++;
    }

    //cull out of bounds
    while (RING_INDEX_POS(items_conveyor, items_conveyor.start).y > LS_LOGICAL_HEIGHT)
    {
        //reroll image
        RING_INDEX_IDS(items_conveyor, items_conveyor.start) = GetRandomShape();
        RING_INDEX_POS(items_conveyor, items_conveyor.start).x = GetRandomValue(0, LS_LOGICAL_WIDTH - RING_INDEX_IDS(items_conveyor, items_conveyor.start)->art.width);
        RING_INDEX_POS(items_conveyor, items_conveyor.start).y = -RING_INDEX_IDS(items_conveyor, items_conveyor.start)->art.height - deploy_cooldown * conveyor_velocity;

        deploy_cooldown += RING_INDEX_IDS(items_conveyor, items_conveyor.start)->art.height / conveyor_velocity;

        //shifts to next position
        items_conveyor.start++;
        if (items_conveyor.start == MAX_BUFFER_SIZE_ITEMS)
        {
            items_conveyor.start = 0;
        }
    }

    for (int i = 0; i < items_conveyor.length; i++)
    {
        RING_INDEX_POS(items_conveyor, i).y += conveyor_velocity;
    }
}