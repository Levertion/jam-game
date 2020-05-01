#ifndef TROLLEY_STATE_GUARD
#define TROLLEY_STATE_GUARD

#include "shapes.h"

typedef struct _item
{
    Shape *shape;
    int posX;
    int posY;
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