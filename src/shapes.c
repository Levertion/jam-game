#include "shapes.h"
#include <stddef.h>

#define NUMBER_OF_SHAPES 7
static Shape AllShapes[NUMBER_OF_SHAPES];

int LoadShapes()
{
    Texture2D longShapeTexture = LoadTexture("assets/LongShape.png");
    Texture2D shortShapeTexture = LoadTexture("assets/ShortShape.png");
    Texture2D dogShapeTexture = LoadTexture("assets/DogShape.png");
    Texture2D pizzaShapeTexture = LoadTexture("assets/PizzaShape.png");
    Texture2D canShapeTexture = LoadTexture("assets/CanShape.png");
    Texture2D fruitShapeTexture = LoadTexture("assets/FruitShape.png");
    Texture2D bananaShapeTexture = LoadTexture("assets/BananaShape.png");

    Shape longshape = {
        {{0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0},
         {0, 1, 1, 1, 1, 1, 1, 0},
         {0, 1, 1, 1, 1, 1, 1, 0},
         {0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0}},
        longShapeTexture};

    Shape shortshape = {
        {{0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 1, 0, 0, 0, 0},
         {0, 0, 0, 1, 0, 0, 0, 0},
         {0, 0, 0, 1, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0}},
        shortShapeTexture};

    Shape dogshape = {
        {{1, 1, 0, 0, 1, 1, 1, 1},
         {1, 1, 0, 0, 1, 1, 1, 1},
         {1, 1, 1, 1, 1, 1, 1, 1},
         {1, 1, 1, 1, 1, 1, 0, 0},
         {1, 1, 1, 1, 1, 1, 0, 0},
         {1, 1, 1, 1, 1, 1, 0, 0},
         {1, 1, 0, 0, 1, 1, 0, 0},
         {1, 1, 0, 0, 1, 1, 0, 0}},
        dogShapeTexture};

    Shape pizzashape = {
        {{0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 1, 1, 1, 1, 0, 0},
         {0, 1, 1, 1, 1, 1, 1, 0},
         {0, 1, 1, 1, 1, 1, 1, 0},
         {0, 1, 1, 1, 1, 1, 1, 0},
         {0, 1, 1, 1, 1, 1, 1, 0},
         {0, 0, 1, 1, 1, 1, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0}},
        pizzaShapeTexture};

    Shape canshape = {
        {{0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 1, 0, 0, 0, 0},
         {0, 0, 0, 1, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0}},
        canShapeTexture};

    Shape fruitshape = {
        {{0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 1, 1, 0, 0, 0, 0},
         {0, 0, 1, 1, 1, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0}},
        fruitShapeTexture};

    Shape bananashape = {
        {{0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 1, 0, 0, 0, 0},
         {0, 0, 0, 1, 1, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0}},
        bananaShapeTexture};

    AllShapes[0] = longshape;
    AllShapes[1] = shortshape;
    AllShapes[2] = dogshape;
    AllShapes[3] = pizzashape;
    AllShapes[4] = canshape;
    AllShapes[5] = fruitshape;
    AllShapes[6] = bananashape;
    return 1;
}

Shape *GetRandomShape()
{
    int id = GetRandomValue(0, NUMBER_OF_SHAPES - 1);
    return &AllShapes[id];
};

int UnLoadShapes()
{
    for (int i = 0; i < NUMBER_OF_SHAPES; i++)
    {
        UnloadTexture(AllShapes[i].art);
    }
}
