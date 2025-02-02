#ifndef LEFTSIDE_LOGIC_GUARD
#define LEFTSIDE_LOGIC_GUARD

#include "raylib.h"
#include "shapes.h"

#define LS_LOGICAL_HEIGHT (900)
#define LS_LOGICAL_WIDTH (600)

#define MAX_BUFFER_SIZE_ITEMS (20)
#define RING_INDEX_RAW(buffer, i) (i + buffer.start - (i + buffer.start >= buffer.length) * buffer.length)
#define RING_INDEX_IDS(buffer, i) (buffer.shapes[i + buffer.start - (i + buffer.start >= buffer.length) * buffer.length])
#define RING_INDEX_POS(buffer, i) (buffer.positions[i + buffer.start - (i + buffer.start >= buffer.length) * buffer.length])

typedef struct
{
    Shape *shapes[MAX_BUFFER_SIZE_ITEMS];
    Vector2 positions[MAX_BUFFER_SIZE_ITEMS];
    bool active[MAX_BUFFER_SIZE_ITEMS];
    int start;
    int length;
} RingBufferItems;

typedef struct
{
    Shape *shape;
} HoldItem;

extern HoldItem current_hold_item_L;
extern HoldItem current_hold_item_R;
extern int conveyor_offset;
extern RingBufferItems items_conveyor;
void leftside_init();
void leftside_logic();
float supply_fraction();
bool is_time_up();
#endif