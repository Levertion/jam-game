#ifndef SHAPES___GUARD____H
#define SHAPES___GUARD____H

#include "raylib.h"
#include "constants.h"

typedef struct Shape
{
    int grid[GRID_ITEM_LEN][GRID_ITEM_LEN];
    Texture2D art;
    int size;
    // Details
} Shape;

Shape *GetRandomShape();
Shape *GetShapeWithIndex(int index);

int LoadShapes();
int UnLoadShapes();

#endif