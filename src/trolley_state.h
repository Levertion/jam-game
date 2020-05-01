#ifndef TROLLEY_STATE_GUARD
#define TROLLEY_STATE_GUARD

#include "shapes.h"

enum Rotation {up, right, down, left};

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
    int numItems;
} TrolleyState;

//initialise the item array if there are no items
//otherwise reallocate memory with the new item added
void add_item(Item item);

#endif