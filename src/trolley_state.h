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
