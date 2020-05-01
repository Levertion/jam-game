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
        RING_INDEX_IDS(items_conveyor, items_conveyor.length) = GetRandomValue(0, NUMBER_OF_SHAPES - 1);
        int id_inquestion = RING_INDEX_IDS(items_conveyor, items_conveyor.length);
        RING_INDEX_POS(items_conveyor, items_conveyor.length).x = GetRandomValue(0, LS_LOGICAL_WIDTH - AllShapes[id_inquestion].art.width);
        RING_INDEX_POS(items_conveyor, items_conveyor.length).y = -AllShapes[RING_INDEX_IDS(items_conveyor, items_conveyor.length)].art.height;

        deploy_cooldown = AllShapes[RING_INDEX_IDS(items_conveyor, items_conveyor.length)].art.height / conveyor_velocity;
        items_conveyor.length++;
    }

    //cull out of bounds
    while (RING_INDEX_POS(items_conveyor, items_conveyor.start).y > LS_LOGICAL_HEIGHT && items_conveyor.length > 0)
    {
        //shifts to next position
        items_conveyor.start++;
        if (items_conveyor.start == MAX_BUFFER_SIZE_ITEMS)
        {
            items_conveyor.start = 0;
        }
        items_conveyor.length--;
    }

    for (int i = 0; i < items_conveyor.length; i++)
    {
        RING_INDEX_POS(items_conveyor, i).y += conveyor_velocity;
    }
}