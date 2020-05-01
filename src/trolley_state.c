#include "trolley_state.h"

#include <stdlib.h>

static TrolleyState the_trolley_state = {.items = NULL, .numItems = 0};

void add_item(Item item)
{
    if (the_trolley_state.items = NULL)
    {
        the_trolley_state.items = malloc(sizeof(Item));
        the_trolley_state.numItems = 1;
    }
    else
    {
        the_trolley_state.items = realloc(the_trolley_state.items, sizeof(Item) * the_trolley_state.numItems + 1);
    }
    the_trolley_state.items[the_trolley_state.numItems++] = item;
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
    return the_trolley_state;
}
