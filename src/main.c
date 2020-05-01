#include "draw_trolley.h"
#include "trolley_state.h"
#include "raylib.h"
#include "leftside_logic.h"
#include "leftside_graphics.h"

#define SCREEN_WIDTH (1600)
#define SCREEN_HEIGHT (900)
#define LEFT_WIDTH (600)
#define DIVIDOR_WIDTH (2)

// Change this depending on the path of your executable relative to the assets folder
#define ASSET_PATH "assets/"

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "PackShoppingGame");

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second

    LoadShapes();

    leftside_init();

    add_initial_items();

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------
        leftside_logic();
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

        DrawTrolleyGrid();

        DrawTrolley(get_state());

        DrawRectangle(LEFT_WIDTH, 0, DIVIDOR_WIDTH, SCREEN_HEIGHT, BLACK);

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