#include "shapes.h"
#include <stddef.h>
Shape AllShapes[3];


int LoadShapes()
{
    Texture2D shortShapeTexture = LoadTexture("assets/ShortShape.png");


    Shape longshape = {
        {
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,1,1,1,1,1,1,0},
        {0,1,1,1,1,1,1,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0}
        },
        NULL
    };

    Shape shortshape = {
        {
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,1,0,0,0,0},
        {0,0,0,1,0,0,0,0},
        {0,0,0,1,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0}
        },
        NULL
    };

    Shape dogshape = {
        {
        {1,1,0,0,1,1,1,1},
        {1,1,0,0,1,1,1,1},
        {1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,0,0},
        {1,1,1,1,1,1,0,0},
        {1,1,1,1,1,1,0,0},
        {1,1,0,0,1,1,0,0},
        {1,1,0,0,1,1,0,0}
        },
        NULL
    };

    AllShapes[0] = longshape;
    AllShapes[1] = shortshape;
    AllShapes[2] = dogshape;
    return 1;
}

