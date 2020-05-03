#include "draw_cache.h"
#include "leftside_logic.h"
#include "constants.h"
#include <stddef.h>
static const Vector2 loc_L = {10 + LEFT_WIDTH, 10}, loc_R = {SCREEN_WIDTH - 280, 10};
static Texture2D hand_L, hand_R, mouse_L, mouse_R;
void load_hands()
{
    Image hand_img, mouse_img;
    hand_img = LoadImage("assets/Hand.png");
    mouse_img = LoadImage("assets/MouseClick.png");
    hand_L = LoadTextureFromImage(hand_img);
    mouse_L = LoadTextureFromImage(mouse_img);
    ImageFlipHorizontal(&hand_img);
    ImageFlipHorizontal(&mouse_img);
    mouse_R = LoadTextureFromImage(mouse_img);
    hand_R = LoadTextureFromImage(hand_img);
    UnloadImage(hand_img);
    UnloadImage(mouse_img);
}
void draw_cache()
{
    DrawTexture(hand_L, loc_L.x, loc_L.y, WHITE);
    DrawTexture(mouse_L, loc_L.x + hand_L.width, loc_L.y, WHITE);
    if (current_hold_item_L.shape != NULL)
    {
        DrawTexture(current_hold_item_L.shape->art, loc_L.x + 40, loc_L.y, WHITE);
    }
    DrawTexture(hand_R, loc_R.x + 40, loc_R.y, WHITE);
    DrawTexture(mouse_R, loc_R.x + 40 - mouse_R.width, loc_R.y, WHITE);
    if (current_hold_item_R.shape != NULL)
    {
        DrawTexture(current_hold_item_R.shape->art, loc_R.x - 40, loc_R.y, WHITE);
    }
}
void unload_hands()
{
    UnloadTexture(hand_L);
    UnloadTexture(hand_R);
    UnloadTexture(mouse_L);
    UnloadTexture(mouse_R);
}