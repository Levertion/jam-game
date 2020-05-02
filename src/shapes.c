#include "shapes.h"
#include <stddef.h>

#define NUMBER_OF_SHAPES 14
static Shape AllShapes[NUMBER_OF_SHAPES];

int LoadShapes()
{
    Texture2D toiletPaperShapeTexture = LoadTexture("assets/ToiletPaperShape.png");
    Texture2D spoonShapeTexture = LoadTexture("assets/SpoonShape.png");
    Texture2D dogShapeTexture = LoadTexture("assets/DogShape.png");
    Texture2D pizzaShapeTexture = LoadTexture("assets/PizzaShape.png");
    Texture2D canShapeTexture = LoadTexture("assets/CanShape.png");
    Texture2D fruitShapeTexture = LoadTexture("assets/FruitShape.png");
    Texture2D bananaShapeTexture = LoadTexture("assets/BananaShape.png");
    Texture2D baguetteShapeTexture = LoadTexture("assets/BaguetteShape.png");
    Texture2D loafShapeTexture = LoadTexture("assets/LoafShape.png");
    Texture2D potatoShapeTexture = LoadTexture("assets/PotatoShape.png");
    Texture2D tomatoShapeTexture = LoadTexture("assets/TomatoShape.png");
    Texture2D juiceShapeTexture = LoadTexture("assets/JuiceShape.png");
    Texture2D riceShapeTexture = LoadTexture("assets/RiceShape.png");
    Texture2D veggiesShapeTexture = LoadTexture("assets/VeggiesShape.png");

    Shape longshape = {
        {{0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0},
         {0, 1, 1, 1, 1, 1, 1, 0},
         {0, 1, 1, 1, 1, 1, 1, 0},
         {0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0}},
        toiletPaperShapeTexture,
    };

    Shape shortshape = {
        {{0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 1, 0, 0, 0, 0},
         {0, 0, 0, 1, 0, 0, 0, 0},
         {0, 0, 0, 1, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0}},
        spoonShapeTexture,
    };

    Shape dogshape = {
        {{1, 1, 0, 0, 1, 1, 1, 1},
         {1, 1, 0, 0, 1, 1, 1, 1},
         {1, 1, 0, 0, 1, 1, 1, 1},
         {1, 1, 1, 1, 1, 1, 0, 0},
         {1, 1, 1, 1, 1, 1, 0, 0},
         {1, 1, 1, 1, 1, 1, 0, 0},
         {1, 1, 0, 0, 1, 1, 0, 0},
         {1, 1, 0, 0, 1, 1, 0, 0}},
        dogShapeTexture,
    };

    Shape pizzashape = {
        {{0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 1, 1, 1, 1, 0, 0},
         {0, 1, 1, 1, 1, 1, 1, 0},
         {0, 1, 1, 1, 1, 1, 1, 0},
         {0, 1, 1, 1, 1, 1, 1, 0},
         {0, 1, 1, 1, 1, 1, 1, 0},
         {0, 0, 1, 1, 1, 1, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0}},
        pizzaShapeTexture,
    };

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

    Shape baguetteshape = {
        {{0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0},
         {0, 1, 1, 1, 1, 1, 1, 0},
         {0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0}},
        baguetteShapeTexture};

    Shape loafshape = {
        {{0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 1, 1, 1, 0, 0, 0},
         {0, 0, 1, 1, 1, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0}},
        loafShapeTexture};

    Shape potatoshape = {
        {{0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 1, 1, 0, 0, 0},
         {0, 0, 1, 1, 1, 1, 0, 0},
         {0, 0, 1, 1, 1, 1, 0, 0},
         {0, 0, 1, 1, 1, 1, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0}},
        potatoShapeTexture};

    Shape tomatoshape = {
        {{0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 1, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0}},
        tomatoShapeTexture};

    Shape juiceshape = {
        {{0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 1, 1, 0, 0, 0},
         {0, 0, 0, 1, 1, 0, 0, 0},
         {0, 0, 0, 1, 1, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0}},
        juiceShapeTexture};

    Shape riceshape = {
        {{0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 1, 1, 1, 0, 0, 0},
         {0, 0, 1, 1, 1, 0, 0, 0},
         {0, 0, 1, 1, 1, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0}},
        riceShapeTexture};

    Shape veggiesshape = {
        {{0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 1, 1, 0, 0, 0},
         {0, 0, 1, 1, 1, 1, 0, 0},
         {0, 0, 1, 1, 1, 1, 0, 0},
         {0, 0, 0, 1, 1, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0}},
        veggiesShapeTexture};

    AllShapes[0] = longshape;
    AllShapes[1] = shortshape;
    AllShapes[2] = dogshape;
    AllShapes[3] = pizzashape;
    AllShapes[4] = canshape;
    AllShapes[5] = fruitshape;
    AllShapes[6] = bananashape;
    AllShapes[7] = baguetteshape;
    AllShapes[8] = loafshape;
    AllShapes[9] = potatoshape;
    AllShapes[10] = tomatoshape;
    AllShapes[11] = juiceshape;
    AllShapes[12] = riceshape;
    AllShapes[13] = veggiesshape;

    for (int i = 0; i < NUMBER_OF_SHAPES; i++)
    {
        int count = 0;
        for (int j = 0; j < GRID_ITEM_LEN; j++)
        {

            Shape this_shape = AllShapes[i];

            for (int k = 0; k < GRID_ITEM_LEN; k++)
            {
                if (this_shape.grid[j][k] == 1)
                {
                    count += 1;
                }
            }
        }

        AllShapes[i].size = count;
    }

    return 1;
}

Shape *GetRandomShape()
{
    int id = GetRandomValue(0, NUMBER_OF_SHAPES - 1);
    return &AllShapes[id];
};

// Temporary for testing
Shape *GetShapeWithIndex(int index)
{
    return &AllShapes[index];
}

int UnLoadShapes()
{
    for (int i = 0; i < NUMBER_OF_SHAPES; i++)
    {
        UnloadTexture(AllShapes[i].art);
    }
}
