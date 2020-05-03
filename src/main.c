#include "draw_trolley.h"
#include "trolley_state.h"
#include "raylib.h"
#include "leftside_logic.h"
#include "leftside_graphics.h"
#include "trolley_logic.h"
#include "draw_cache.h"
#include "audio.h"
#include "timer.h"
#include <stdlib.h>
#include <emscripten/emscripten.h>

#define SCREEN_WIDTH (1600)
#define SCREEN_HEIGHT (900)
#define LEFT_WIDTH (600)
#define DIVIDOR_WIDTH (2)

#define POINTS_TEXT_SIZE (10)

// Change this depending on the path of your executable relative to the assets folder
#define ASSET_PATH "assets/"

int points = 0;
bool in_menu = true;
TrolleyState trolley;
Rectangle start_button_bounding_box;

void UpdateDrawFrame()
{
    // Update
    //----------------------------------------------------------------------------------
    // TODO: Update your variables here
    //----------------------------------------------------------------------------------
    if (in_menu)
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), start_button_bounding_box))
            in_menu = false;
    }
    else
    {
        update_audio();
        leftside_logic();
        bool allIn;

        points = CalculateAreaFilled(&trolley, &allIn);

        if (allIn && is_time_up() && current_hold_item_L.shape == NULL && current_hold_item_R.shape == NULL)
        {
            finish_game();
        }
        else if (is_time_up() && is_checkout_button_pressed())
        {
            finish_game();
        }
        if (!game_ended())
        {
            TrolleyFrame(&trolley);
        }
    }
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

    DrawTrolleyBackground();

    draw_cache();

    if (is_time_up())
    {
        draw_timer();
    }

    DrawTrolleyGrid();

    DrawTrolley(&trolley);
    IsColliding(&trolley);

    DrawRectangle(LEFT_WIDTH, 0, DIVIDOR_WIDTH, SCREEN_HEIGHT, BLACK);

    DrawText(TextFormat("Points: %d", points), 1450, 800, 20, DARKGREEN);
    EndScissorMode();
    if (in_menu)
    {
        ;
        if (CheckCollisionPointRec(GetMousePosition(), start_button_bounding_box))
            DrawText("START", start_button_bounding_box.x, start_button_bounding_box.y, 100, MAROON);
        else

            DrawText("START", start_button_bounding_box.x, start_button_bounding_box.y, 100, RED);
    }
    EndDrawing();
}

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Stock and Shop");
    InitAudioDevice();
    //  SetTargetFPS(60); // Set our game to run at 60 frames-per-second
    init_audio();
    LoadShapes();
    load_hands();
    leftside_init();
    LoadTrolleyTextures();
    load_leftside_textures();

    //start button
    Vector2 start_button_dimensions = MeasureTextEx(GetFontDefault(), "START", 100, 1);
    start_button_bounding_box = (Rectangle){SCREEN_WIDTH / 2 - start_button_dimensions.x / 2, SCREEN_HEIGHT / 2 - start_button_dimensions.y, start_button_dimensions.x, start_button_dimensions.y};

    trolley = DefaultState();

    AddRandomItems(&trolley);

    emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
    // Main game loop
    // while (!WindowShouldClose()) // Detect window close button or ESC key
    // {

    //     //----------------------------------------------------------------------------------
    // }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnLoadShapes();
    unload_hands();
    unload_leftside_textures();
    unload_audio();
    CloseAudioDevice();
    CloseWindow(); // Close window and OpenGL context

    return 0;
}
