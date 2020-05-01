#include "trolley_state.h"
#include "raylib.h"

#include <stdlib.h>

#define INITIAL_CAPACITY 4

static TrolleyState state = {.items = NULL, .numItems = 0, .capacity = 0};

void add_item(Item item)
{
    if (state.capacity <= state.numItems)
    {
        if (state.capacity == 0)
        {
            state.capacity = INITIAL_CAPACITY;
        }
        else
        {
            state.capacity *= 2;
        }
        state.items = realloc(state.items, sizeof(Item) * state.capacity);
    }
    state.items[state.numItems] = item;
    state.numItems++;
}

void add_initial_items()
{
    for (int i = 0; i < 4; i++)
    {
        add_item((Item){
            .shape = GetRandomShape(),
            .posX = GetRandomValue(0, 10),
            .posY = GetRandomValue(0, 10),
            .rotation = GetRandomValue(0, 3)});
        /* code */
    }

    // add_item((Item){
    //     .shape = GetShapeWithIndex(1),
    //     .posX = 0,
    //     .posY = 0,
    //     .rotation = 0});
}

void DeleteAllItems()
{
    state.numItems = 0;
}

TrolleyState get_state()
{
    return state;
}
