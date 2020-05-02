#include "trolley_state.h"
#include "raylib.h"

#include <stdlib.h>
#include "trolley_logic.h"

#define INITIAL_CAPACITY 4

TrolleyState DefaultState()
{
    return (TrolleyState){.items = NULL, .capacity = 0, .len = 0, .draggedX = -1, .draggedY = -1, .draggedItem = -1};
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
    int count = 0;
    for (int i = 0; i < 20; i++)
    {
        Item item;
        do
        {
            if (count > 1000)
            {
                return;
            }
            item = (Item){
                .shape = GetRandomShape(),
                .posX = GetRandomValue(-5, TROLLEY_WIDTH - 5),
                .posY = GetRandomValue(-BLOCKS_ABOVE_TROLLEY - 5, TROLLEY_HEIGHT - 5),
                .rotation = GetRandomValue(0, 3),
                .gravityCooldown = GRAVITY_FRAMES};
            count++;
        } while (WouldCollide(state, item, -1));
        AddItem(state, item);
    }
}

void DeleteAllItems(TrolleyState *state)
{
    state->len = 0;
}
