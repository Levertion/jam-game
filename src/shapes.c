#include "shapes.h"
#include <stddef.h>



int LoadShapes()
{
    Texture2D longShapeTexture = LoadTexture("assets/LongShape.png");
    Texture2D shortShapeTexture = LoadTexture("assets/ShortShape.png");
    Texture2D dogShapeTexture = LoadTexture("assets/DogShape.png");
    Texture2D pizzaShapeTexture = LoadTexture("assets/PizzaShape.png");


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
        longShapeTexture
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
        shortShapeTexture
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
        dogShapeTexture
    }; 

    Shape pizzashape = {
        {
        {0,0,0,0,0,0,0,0},
        {0,0,1,1,1,1,0,0},
        {0,1,1,1,1,1,1,0},
        {0,1,1,1,1,1,1,0},
        {0,1,1,1,1,1,1,0},
        {0,1,1,1,1,1,1,0},
        {0,0,1,1,1,1,0,0},
        {0,0,0,0,0,0,0,0}
        },
        pizzaShapeTexture
    };

    AllShapes[0] = longshape;
    AllShapes[1] = shortshape;
    AllShapes[2] = dogshape;
    AllShapes[3] = pizzashape;
    return 1;
}

