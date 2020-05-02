#include "trolley_state.h"
#include "trolley_logic.h"
#include "stdbool.h"
#include "stdio.h"
#include "raylib.h"
#include "constants.h"

Item MoveItem(Item item, enum Direction dir)
{
    Item result = item;
    switch (dir)
    {
    case Up:
        item.posY -= 1;
        break;
    case Down:
        item.posY += 1;
        break;
    case Left:
        item.posX -= 1;
        break;
    case Right:
        item.posY += 1;
        break;
    default:
        break;
    }
    return result;
}

struct Range
{
    int start;
    int end;
};

static struct Range Overlap(int a, int alen, int b, int blen)
{
    int aEnd = a + alen;
    int bEnd = b + blen;
    return (struct Range){
        .start =
            (a > b) ? a : b,
        .end = (aEnd < bEnd) ? aEnd : bEnd};
}

struct IntVector2
{
    int i;
    int j;
};

#define GRID_ITEM_MAX (GRID_ITEM_LEN - 1)

static struct IntVector2 ShapeCoordsUndoRotation(int x, int y, enum Rotation rotation)
{
    int i = 0;
    int j = 0;
    switch (rotation)
    {
    case up:
        i = x;
        j = y;
        break;
    case down:
        i = GRID_ITEM_MAX - x;
        j = GRID_ITEM_MAX - y;
        break;
    case left:
        i = GRID_ITEM_MAX - y;
        j = x;
        break;
    case right:
        i = y;
        j = GRID_ITEM_MAX - x;
        break;
    default:
        break;
    }
    return (struct IntVector2){.i = i, .j = j};
}

static bool IsCollidingWithOutside(Item item)
{
    bool result = false;
    for (int y = 0; y < GRID_ITEM_LEN; y++)
    {
        for (int x = 0; x < GRID_ITEM_LEN; x++)
        {
            int gridX = x + item.posX;
            int gridY = y + item.posY;
            if (gridX < 0 || gridY < 0 || gridX >= TROLLEY_WIDTH || gridY >= TROLLEY_HEIGHT)
            {
                struct IntVector2 res = ShapeCoordsUndoRotation(x, y, item.rotation);
                if (item.shape->grid[res.j][res.i])
                {
                    result = true;
                    // Debug box to show where collisioned happened
                    Vector2 render_pos = {
                        889 + ((float)gridX) * GRID_BLOCK_LENGTH + 10,
                        360 + ((float)gridY) * GRID_BLOCK_LENGTH + 10};
                    Color c = BLUE;
                    c.a = 200;
                    DrawRectangleV(render_pos, (Vector2){10, 10}, c);
                }
            }
        }
    }
    return result;
}

static bool ItemsCollide(Item item, Item item2)
{
    bool collided = false;
    // TODO?: Change to use bitshifts
    int xOffset = item2.posX - item.posX;
    struct Range xOverlap = Overlap(0, GRID_ITEM_LEN, xOffset, GRID_ITEM_MAX);

    int yOffset = item2.posY - item.posY;
    struct Range yOverlap = Overlap(0, GRID_ITEM_MAX, yOffset, GRID_ITEM_MAX);

    for (int x = xOverlap.start; x < xOverlap.end; x++)
    {
        for (int y = yOverlap.start; y < yOverlap.end; y++)
        {
            struct IntVector2 itemPositions = ShapeCoordsUndoRotation(x, y, item.rotation);
            struct IntVector2 item2Positions = ShapeCoordsUndoRotation(x - xOffset, y - yOffset, item2.rotation);
            if (item.shape->grid[itemPositions.j][itemPositions.i] && item2.shape->grid[item2Positions.j][item2Positions.i])
            {
                collided = true;

                // Debug box to show where collisioned happened
                Vector2 render_pos = {
                    889 + ((float)item.posX + x) * GRID_BLOCK_LENGTH + 10,
                    360 + ((float)item.posY + y) * GRID_BLOCK_LENGTH + 10};
                Color c = RED;
                c.a = 200;
                DrawRectangleV(render_pos, (Vector2){10, 10}, c);
            }
        }
    }
    return collided;
}

bool WouldCollide(const TrolleyState *state, Item item, int exclude)
{
    bool result = false;
    for (int i = 0; i < state->len; i++)
    {
        if (i != exclude)
        {
            Item item2 = state->items[i];
            if (ItemsCollide(item, item2))
            {
                result = true;
            }
        }
    }
    return result;
}

bool IsColliding(const TrolleyState *state)
{
    bool result = false;
    for (int i = 0; i < state->len; i++)
    {
        if (WouldCollide(state, state->items[i], i))
        {
            result = true;
        }
        // Don't short circuit for debug output
        if (IsCollidingWithOutside(state->items[i]))
        {
            result = true;
        }
    }
    return result;
}

bool CanMoveItem(const TrolleyState *state, int itemIdx, enum Direction dir)
{
    Item moved = MoveItem(state->items[itemIdx], dir);
    return !WouldCollide(state, moved, itemIdx);
}
