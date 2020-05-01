#include "trolley_state.h"
#include "trolley_logic.h"
#include "stdbool.h"
#include "stdio.h"
#include "raylib.h"

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
        i = 7 - x;
        j = 7 - y;
        break;
    case left:
        i = 7 - y;
        j = x;
        break;
    case right:
        i = y;
        j = 7 - x;
        break;
    default:
        break;
    }
    return (struct IntVector2){.i = i, .j = j};
}

static bool ItemsCollide(Item item, Item item2)
{
    bool collided = false;
    // TODO?: Change to use bitshifts
    int xOffset = item2.posX - item.posX;
    struct Range xOverlap = Overlap(0, 8, xOffset, 8);

    int yOffset = item2.posY - item.posY;
    struct Range yOverlap = Overlap(0, 8, yOffset, 8);

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
                    889 + ((float)item.posX + x) * 30 + 10,
                    360 + ((float)item.posY + y) * 30 + 10};
                Color c = GREEN;
                c.a = 50;
                DrawRectangleV(render_pos, (Vector2){10, 10}, c);
            }
        }
    }
    return collided;
}

bool WouldCollide(TrolleyState state, Item item, int exclude)
{
    bool result = false;
    for (int i = 0; i < state.numItems; i++)
    {
        if (i != exclude)
        {
            Item item2 = state.items[i];
            if (ItemsCollide(item, item2))
            {
                result = true;
            }
        }
    }
    return result;
}

bool IsColliding(TrolleyState state)
{
    bool result = false;
    // Last item has already been fully checked
    for (int i = 0; i < state.numItems; i++)
    {
        if (WouldCollide(state, state.items[i], i))
        {
            result = true;
        }
    }
    return result;
}

bool CanMoveItem(TrolleyState state, int itemIdx, enum Direction dir)
{
    Item moved = MoveItem(state.items[itemIdx], dir);
    return !WouldCollide(state, moved, itemIdx);
}
