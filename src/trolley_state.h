#ifndef TROLLEY_STATE_GUARD
#define TROLLEY_STATE_GUARD

#include "shapes.h"

enum Rotation
{
    up,
    right,
    down,
    left
};

typedef struct _item
{
    Shape *shape;
    int posX;
    int posY;
    enum Rotation rotation;
} Item;

typedef struct _trolleyState
{
    Item *items;
    int len;
    int capacity;
} TrolleyState;

TrolleyState DefaultState();

void AddItem(TrolleyState *state, Item item);
void AddRandomItems(TrolleyState *state);
void DeleteAllItems(TrolleyState *state);

#endif