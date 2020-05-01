#ifndef SHAPES___GUARD____H
#define SHAPES___GUARD____H

#include "raylib.h"

typedef struct Shape
{
    int grid[8][8];
    Texture2D art;
    // Details
} Shape;

Shape *GetRandomSShape();

#endif