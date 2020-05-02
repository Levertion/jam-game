#include "trolley_state.h"
#include "trolley_logic.h"
#include "stdbool.h"
#include "stdio.h"
#include "raylib.h"
#include "constants.h"

void MoveItem(Item *item, enum Direction dir)
{
    switch (dir)
    {
    case DirUp:
        item->posY -= 1;
        break;
    case DirDown:
        item->posY += 1;
        break;
    case DirLeft:
        item->posX -= 1;
        break;
    case DirRight:
        item->posX += 1;
        break;
    default:
        break;
    }
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
    case RotUp:
        i = x;
        j = y;
        break;
    case RotDown:
        i = GRID_ITEM_MAX - x;
        j = GRID_ITEM_MAX - y;
        break;
    case RotLeft:
        i = GRID_ITEM_MAX - y;
        j = x;
        break;
    case RotRight:
        i = y;
        j = GRID_ITEM_MAX - x;
        break;
    default:
        break;
    }
    return (struct IntVector2){.i = i, .j = j};
}

static bool IsCollidingWithOutside(Item item, int minHeight)
{
    bool result = false;
    for (int y = 0; y < GRID_ITEM_LEN; y++)
    {
        for (int x = 0; x < GRID_ITEM_LEN; x++)
        {
            int gridX = x + item.posX;
            int gridY = y + item.posY;
            if (gridX < 0 || gridY < minHeight || gridX >= TROLLEY_WIDTH || gridY >= TROLLEY_HEIGHT)
            {
                struct IntVector2 res = ShapeCoordsUndoRotation(x, y, item.rotation);
                if (item.shape->grid[res.j][res.i])
                {
                    result = true;
                    // Debug box to show where collisioned happened
                    // Vector2 render_pos = {
                    //     TROLLEY_X + ((float)gridX) * GRID_BLOCK_LENGTH + 10,
                    //     TROLLEY_Y + ((float)gridY) * GRID_BLOCK_LENGTH + 10};
                    // Color c = BLUE;
                    // c.a = 200;
                    // DrawRectangleV(render_pos, (Vector2){10, 10}, c);
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
    struct Range xOverlap = Overlap(0, GRID_ITEM_LEN, xOffset, GRID_ITEM_LEN);

    int yOffset = item2.posY - item.posY;
    struct Range yOverlap = Overlap(0, GRID_ITEM_LEN, yOffset, GRID_ITEM_LEN);

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
                    TROLLEY_X + ((float)item.posX + x) * GRID_BLOCK_LENGTH + 10,
                    TROLLEY_Y + ((float)item.posY + y) * GRID_BLOCK_LENGTH + 10};
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
    if (IsCollidingWithOutside(item, -BLOCKS_ABOVE_TROLLEY))
    {
        result = true;
    }
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
        if (IsCollidingWithOutside(state->items[i], -BLOCKS_ABOVE_TROLLEY))
        {
            result = true;
        }
    }
    return result;
}

bool CanMoveItem(const TrolleyState *state, int itemIdx, enum Direction dir)
{
    Item clone = state->items[itemIdx];
    MoveItem(&clone, dir);
    return !WouldCollide(state, clone, itemIdx) && !IsCollidingWithOutside(clone, -BLOCKS_ABOVE_TROLLEY);
}

static int TryMoveN(TrolleyState *state, int itemIdx, int *amount, enum Direction posDir, enum Direction negDir)
{
    bool neg = false;
    enum Direction dir = posDir;
    if (*amount < 0)
    {
        *amount = -*amount;
        dir = negDir;
        neg = true;
    }
    for (int i = 0; i < *amount; i++)
    {
        if (CanMoveItem(state, itemIdx, dir))
        {
            MoveItem(&state->items[itemIdx], dir);
        }
        else
        {
            *amount -= i;
            if (neg)
            {
                *amount = -*amount;
            }
            return i;
        }
    }
    *amount = 0;
    return 0;
}

void TrolleyFrame(TrolleyState *state)
{
    bool clicking = IsMouseButtonDown(MOUSE_LEFT_BUTTON);
    bool rotating = IsKeyPressed(KEY_R);
    if (clicking || state->draggedItem != -1)
    {
        // Dragging
        Vector2 mouse = GetMousePosition();
        int mouseX = (int)mouse.x;
        int mouseY = (int)mouse.y;
        int mouseBlockX = (mouseX - TROLLEY_X) / GRID_BLOCK_LENGTH;
        int mouseBlockY = (mouseY - TROLLEY_Y) / GRID_BLOCK_LENGTH;
        if (state->draggedItem != -1)
        {
            int draggedX = state->draggedX;
            int draggedY = state->draggedY;
            int horizontal = mouseBlockX - draggedX;
            int vertical = mouseBlockY - draggedY;
            int moved = 0;
            do
            {
                moved = 0;
                moved += TryMoveN(state, state->draggedItem, &vertical, DirDown, DirUp);
                moved += TryMoveN(state, state->draggedItem, &horizontal, DirRight, DirLeft);
            } while (moved != 0);
            state->draggedX = mouseBlockX;
            state->draggedY = mouseBlockY;

            //ROTATE CHECK
            if (rotating)
            {
                enum Rotation NewRotation = (state->items[state->draggedItem].rotation + 1) % 4;
                /*
                Item newItem = (Item)
                {
                    .shape = state->items[state->draggedItem].shape,
                    .posX = state->items[state->draggedItem].posX,
                    .posY = state->items[state->draggedItem].posY,
                    .gravityCooldown = state->items[state->draggedItem].gravityCooldown,
                    .rotation = NewRotation,
                };
                */
                Item newItem = state->items[state->draggedItem];
                newItem.rotation = NewRotation;

                if (WouldCollide(state, newItem, state->draggedItem))
                {
                    //do something
                }
                else
                {
                    state->items[state->draggedItem].rotation = NewRotation;
                }
            }

            //ROTATE CHECK END

            // Try moving
            if (!clicking || horizontal > 0 || vertical > 0)
            {
                state->items[state->draggedItem].gravityCooldown = GRAVITY_FRAMES;
                state->draggedX = -1;
                state->draggedY = -1;
                state->draggedItem = -1;
            }
        }
        else if (clicking)
        {
            for (int i = 0; i < state->len; i++)
            {
                Item item = state->items[i];
                int xOffset = mouseBlockX - item.posX;
                int yOffset = mouseBlockY - item.posY;
                if (xOffset >= 0 && xOffset < GRID_ITEM_LEN && yOffset >= 0 && yOffset < GRID_ITEM_LEN)
                {
                    struct IntVector2 coords = ShapeCoordsUndoRotation(xOffset, yOffset, item.rotation);
                    if (item.shape->grid[coords.i][coords.j])
                    {
                        state->draggedX = mouseBlockX;
                        state->draggedY = mouseBlockY;
                        state->draggedItem = i;
                        state->items[i].gravityCooldown = -1;
                        break;
                    }
                }
            }
        }
    }

    /// Gravity
    for (int i = 0; i < state->len; i++)
    {
        Item *item = &state->items[i];
        if (item->gravityCooldown >= 1)
        {
            item->gravityCooldown -= 1;
        }
        if (item->gravityCooldown == 0)
        {
            if (CanMoveItem(state, i, DirDown))
            {
                MoveItem(item, DirDown);
                item->gravityCooldown = GRAVITY_FRAMES;
            }
        }
    }
}

int CalculateAreaFilled(TrolleyState *state)
{
    int area_filled = 0;

    for (int i = 0; i < state->len; i++)
    {
        Item this_item = state->items[i];
        if (IsCollidingWithOutside(this_item, 0))
        {
            continue;
        }

        area_filled += this_item.shape->size;
    }

    return area_filled;
}
