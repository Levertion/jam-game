#include "draw_trolley.h"
#include "raylib.h"

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

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawRectangle(LEFT_WIDTH - (DIVIDOR_WIDTH / 2), 0, DIVIDOR_WIDTH, SCREEN_HEIGHT, BLACK);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow(); // Close window and OpenGL context

    return 0;
}