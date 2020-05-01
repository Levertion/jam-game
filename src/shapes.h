#ifndef SHAPES___GUARD____H
#define SHAPES___GUARD____H

#include "raylib.h"
#define NUMBER_OF_SHAPES 4

typedef struct Shape
{
    int grid[8][8];
    Texture2D art;
    // Details
} Shape;

Shape AllShapes[NUMBER_OF_SHAPES];

Shape *GetRandomSShape();

int LoadShapes();

#endif