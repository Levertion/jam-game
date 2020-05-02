#include "trolley_state.h"
#include "raylib.h"

#include <stdlib.h>

#define INITIAL_CAPACITY 4

TrolleyState DefaultState()
{
    return (TrolleyState){.items = NULL, .capacity = 0, .len = 0};
}

void AddItem(TrolleyState *state, Item item)
{
    if (state->capacity <= state->len)
    {
        if (state->capacity == 0)
        {
            state->capacity = INITIAL_CAPACITY;
        }
        else
        {
            state->capacity *= 2;
        }
        state->items = realloc(state->items, sizeof(Item) * state->capacity);
    }
    state->items[state->len] = item;
    state->len++;
}

void AddRandomItems(TrolleyState *state)
{
    for (int i = 0; i < 4; i++)
    {
        AddItem(state, (Item){
                           .shape = GetRandomShape(),
                           .posX = GetRandomValue(-5, TROLLEY_WIDTH),
                           .posY = GetRandomValue(-5, TROLLEY_HEIGHT),
                           .rotation = GetRandomValue(0, 3)});
    }
}

void DeleteAllItems(TrolleyState *state)
{
    state->len = 0;
}
