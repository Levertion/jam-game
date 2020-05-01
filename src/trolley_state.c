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

TrolleyState get_state()
{
    return state;
}
