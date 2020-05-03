#ifndef LEFTSIDE_GRAPHICS_GUARD
#define LEFTSIDE_GRAPHICS_GUARD
#include "shapes.h"
#define CONVEYOR_DRAW_OFFSET (149)
Texture2D conveyor_text;
void load_leftside_textures();
void draw_leftside();
void yeet_shape(Shape *shape);
void unload_leftside_textures();
#endif