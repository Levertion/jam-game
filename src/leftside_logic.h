#ifndef LEFTSIDE_LOGIC_GUARD
#define LEFTSIDE_LOGIC_GUARD

#include "raylib.h"
#include "shapes.h"

#define MAX_BUFFER_SIZE_ITEMS (20)
#define RING_INDEX_IDS(buffer, i) (buffer.shapes[i + buffer.start - (i + buffer.start >= buffer.length) * buffer.length])
#define RING_INDEX_POS(buffer, i) (buffer.positions[i + buffer.start - (i + buffer.start >= buffer.length) * buffer.length])
typedef struct
{
    Shape *shapes[MAX_BUFFER_SIZE_ITEMS];
    Vector2 positions[MAX_BUFFER_SIZE_ITEMS];
    int start;
    int length;
} RingBufferItems;
RingBufferItems items_conveyor;
void leftside_init();
void leftside_logic();
#endif