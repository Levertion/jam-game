#include "raylib.h"

typedef struct Shape
{
    bool grid[6][6];
    Texture2D art;
    // Details
} Shape;

Shape GetRandomShape();
