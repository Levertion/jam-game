#ifndef __TROLLEY__LOGIC__H__GUARD
#define __TROLLEY__LOGIC__H__GUARD

#include "trolley_state.h"
#include "stdbool.h"

enum Direction
{
    Up,
    Down,
    Left,
    Right
};

Item MoveItem(Item item, enum Direction dir);
bool WouldCollide(const TrolleyState *state, Item item, int exclude);
bool CanMoveItem(const TrolleyState *state, int itemIdx, enum Direction dir);
bool IsColliding(const TrolleyState *state);

#endif