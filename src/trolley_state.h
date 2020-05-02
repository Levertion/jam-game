#ifndef TROLLEY_STATE_GUARD
#define TROLLEY_STATE_GUARD

#include "shapes.h"

enum Rotation
{
    RotUp,
    RotRight,
    RotDown,
    RotLeft
};

typedef struct _item
{
    Shape *shape;
    int posX;
    int posY;
    int gravityCooldown;
    enum Rotation rotation;
} Item;

typedef struct _trolleyState
{
    Item *items;
    int len;
    int capacity;

    int draggedX;
    int draggedY;
    int draggedItem;
} TrolleyState;

TrolleyState DefaultState();

void AddItem(TrolleyState *state, Item item);
void AddRandomItems(TrolleyState *state);
void DeleteAllItems(TrolleyState *state);

#endif