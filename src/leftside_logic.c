#include "leftside_logic.h"
#include "raylib.h"
#include "shapes.h"
#include "leftside_graphics.h"
#include <stddef.h>
static const int conveyor_velocity = 5;
int conveyor_offset = 0;
static int deploy_cooldown = 0;
static const int max_supply = 60;
static int supply;
static int active_items = MAX_BUFFER_SIZE_ITEMS;
#define CONVEYOR_END (CONVEYOR_DRAW_OFFSET + conveyor_text.width)

static void reroll_item(int i)
{
    items_conveyor.shapes[i] = GetRandomShape();
    //find bounds (in grid blocks)
    int bound_left = GRID_ITEM_LEN, bound_right = GRID_ITEM_LEN, bound_curr;
    for (int j = 0; j < GRID_ITEM_LEN; j++)
    {
        bound_curr = 0;
        for (int k = 0; k < GRID_ITEM_LEN && items_conveyor.shapes[i]->grid[j][k] != 1; k++)
        {
            bound_curr++;
        }
        if (bound_curr < bound_left)
            bound_left = bound_curr;
    }
    for (int j = 0; j < GRID_ITEM_LEN; j++)
    {
        bound_curr = 0;
        for (int k = GRID_ITEM_LEN - 1; k > 0 && items_conveyor.shapes[i]->grid[j][k] != 1; k--)
        {
            bound_curr++;
        }
        if (bound_curr < bound_right)
            bound_right = bound_curr;
    }

    items_conveyor.positions[i].x = (float)GetRandomValue(CONVEYOR_DRAW_OFFSET - bound_left * items_conveyor.shapes[i]->art.width / GRID_ITEM_LEN,
                                                          CONVEYOR_END - items_conveyor.shapes[i]->art.width + bound_right * items_conveyor.shapes[i]->art.width / GRID_ITEM_LEN);
    items_conveyor.positions[i].y = (float)-items_conveyor.shapes[i]->art.height - deploy_cooldown * conveyor_velocity;
    deploy_cooldown += items_conveyor.shapes[i]->art.height / conveyor_velocity;
    items_conveyor.active[i] = 1;
}
float supply_fraction()
{
    return ((float)supply / max_supply);
}
bool is_time_up()
{
    return (active_items == 0);
}
void leftside_init()
{
    supply = max_supply;
    items_conveyor.start = 0;
    items_conveyor.length = 0;
    current_hold_item_L.shape = NULL;
    current_hold_item_R.shape = NULL;
}
void leftside_logic()
{
    //generate shapes if required
    if (deploy_cooldown > 0)
    {
        deploy_cooldown--;
    }
    else if (items_conveyor.length < MAX_BUFFER_SIZE_ITEMS && supply > 0)
    {

        reroll_item(items_conveyor.length);
        supply--;
        items_conveyor.length++;
    }

    //cull out of bounds
    while (RING_INDEX_POS(items_conveyor, 0).y > LS_LOGICAL_HEIGHT + RING_INDEX_IDS(items_conveyor, 0)->art.height && active_items > 0)
    {
        if (supply > 0)
        {
            //reroll image
            reroll_item(RING_INDEX_RAW(items_conveyor, 0));

            supply--;
        }
        else
            active_items--;
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
        if (items_conveyor.active[RING_INDEX_RAW(items_conveyor, i)] && (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON) || IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) && GetMouseX() >= RING_INDEX_POS(items_conveyor, i).x && GetMouseX() <= RING_INDEX_POS(items_conveyor, i).x + RING_INDEX_IDS(items_conveyor, i)->art.width && GetMouseY() >= RING_INDEX_POS(items_conveyor, i).y && GetMouseY() <= RING_INDEX_POS(items_conveyor, i).y + RING_INDEX_IDS(items_conveyor, i)->art.height)
        {
            mouse_block_x = (int)(GetMouseX() - RING_INDEX_POS(items_conveyor, i).x) / (RING_INDEX_IDS(items_conveyor, i)->art.width / GRID_ITEM_LEN);
            mouse_block_y = (int)(GetMouseY() - RING_INDEX_POS(items_conveyor, i).y) / (RING_INDEX_IDS(items_conveyor, i)->art.height / GRID_ITEM_LEN);
            if (RING_INDEX_IDS(items_conveyor, i)->grid[mouse_block_y][mouse_block_x] == 1)
            {
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    if (current_hold_item_L.shape != NULL)
                    {
                        if (current_hold_item_R.shape == NULL)
                        {
                            current_hold_item_R.shape = RING_INDEX_IDS(items_conveyor, i);
                        }
                        else
                        {
                            yeet_shape(current_hold_item_L.shape);
                            current_hold_item_L.shape = RING_INDEX_IDS(items_conveyor, i);
                        }
                    }
                    else
                        current_hold_item_L.shape = RING_INDEX_IDS(items_conveyor, i);
                }
                else
                {
                    if (current_hold_item_R.shape != NULL)
                    {
                        if (current_hold_item_L.shape == NULL)
                        {
                            current_hold_item_L.shape = RING_INDEX_IDS(items_conveyor, i);
                        }
                        else
                        {
                            yeet_shape(current_hold_item_R.shape);
                            current_hold_item_R.shape = RING_INDEX_IDS(items_conveyor, i);
                        }
                    }
                    else
                        current_hold_item_R.shape = RING_INDEX_IDS(items_conveyor, i);
                }
                items_conveyor.active[RING_INDEX_RAW(items_conveyor, i)] = 0;
                break;
            }
        }
    }
    if (active_items > 0)
    {
        //move items
        for (int i = 0; i < items_conveyor.length; i++)
        {
            RING_INDEX_POS(items_conveyor, i).y += conveyor_velocity;
        }
        //move conveyor
        conveyor_offset += conveyor_velocity;
        if (conveyor_offset >= 0)
        {
            conveyor_offset -= conveyor_text.height;
        }
    }
}