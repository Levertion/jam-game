#include "draw_trolley.h"
#include "trolley_state.h"
#include "raylib.h"
#include "leftside_logic.h"
#include "leftside_graphics.h"
#include "trolley_logic.h"
#include "draw_cache.h"

#include <stdlib.h>

#define SCREEN_WIDTH (1600)
#define SCREEN_HEIGHT (900)
#define LEFT_WIDTH (600)
#define DIVIDOR_WIDTH (2)

#define POINTS_TEXT_SIZE (10)

// Change this depending on the path of your executable relative to the assets folder
#define ASSET_PATH "assets/"

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "PackShoppingGame");

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second

    LoadShapes();
    load_hands();
    leftside_init();
    load_leftside_textures();
    int points = 0;
    char points_text[POINTS_TEXT_SIZE];
    TrolleyState trolley = DefaultState();

    AddRandomItems(&trolley);

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------
        leftside_logic();
        if (IsKeyPressed(KEY_R))
        {
            DeleteAllItems(&trolley);
            AddRandomItems(&trolley);
        }

        points = CalculateAreaFilled(&trolley);

        TrolleyFrame(&trolley);
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        //left side
        BeginScissorMode(0, 0, LEFT_WIDTH, SCREEN_HEIGHT);

        draw_leftside();

        EndScissorMode();

        //right side
        BeginScissorMode(LEFT_WIDTH, 0, SCREEN_WIDTH - LEFT_WIDTH, SCREEN_HEIGHT);

        ClearBackground(RAYWHITE);

        draw_cache();

        DrawTrolleyGrid();

        DrawTrolley(&trolley);
        IsColliding(&trolley);

        DrawRectangle(LEFT_WIDTH, 0, DIVIDOR_WIDTH, SCREEN_HEIGHT, BLACK);

        DrawText(itoa(points, &points_text, 10), 1500, 800, 20, DARKGREEN);

        EndScissorMode();

        EndDrawing();

        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnLoadShapes();
    CloseWindow(); // Close window and OpenGL context

    return 0;
}