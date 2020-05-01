#include "raylib.h"

typedef struct Shape
{
    int grid[8][8];
    Texture2D art;
    // Details
} Shape;

Shape GetRandomShape();
