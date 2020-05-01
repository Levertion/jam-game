#include "trolley_state.h"
#include "trolley_logic.h"
#include "stdbool.h"

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

static bool ItemsCollide(Item item, Item item2)
{
    // TODO?: Change to use bitshifts
    int xOffset = item2.posX - item.posX;
    struct Range xOverlap = Overlap(0, 6, xOffset, 6);

    int yOffset = item2.posX - item.posX;
    struct Range yOverlap = Overlap(0, 6, xOffset, 6);

    for (int i = xOverlap.start; i < xOverlap.end; i++)
    {
        for (int j = yOverlap.start; j < yOverlap.end; j++)
        {
            if (item.shape->grid[i][j] && item2.shape->grid[i + xOffset][j + yOffset])
            {
                return true;
            }
        }
    }
    return false;
}

bool WouldCollide(TrolleyState state, Item item, int exclude)
{
    for (int i = 0; i < state.numItems; i++)
    {
        if (i != exclude)
        {
            Item item2 = state.items[i];
            if (ItemsCollide(item, item2))
            {
                return true;
            }
        }
    }
    return false;
}

bool CanMoveItem(TrolleyState state, int itemIdx, enum Direction dir)
{
    Item moved = MoveItem(state.items[itemIdx], dir);
    return !WouldCollide(state, moved, itemIdx);
}
