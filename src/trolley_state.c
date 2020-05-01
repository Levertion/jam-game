#include "trolley_state.h"

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
    Item item1 = {
        .shape = GetRandomShape(),
        .posX = 0,
        .posY = 0,
        .rotation = 0};
    add_item(item1);
}

TrolleyState get_state()
{
    return state;
}
