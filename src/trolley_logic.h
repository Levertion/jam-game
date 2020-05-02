#ifndef __TROLLEY__LOGIC__H__GUARD
#define __TROLLEY__LOGIC__H__GUARD

#include "trolley_state.h"
#include "stdbool.h"

enum Direction
{
    DirUp,
    DirDown,
    DirLeft,
    DirRight
};

void MoveItem(Item *item, enum Direction dir);
bool WouldCollide(const TrolleyState *state, Item item, int exclude);
bool CanMoveItem(const TrolleyState *state, int itemIdx, enum Direction dir);
bool IsColliding(const TrolleyState *state);
void TrolleyFrame(TrolleyState *state);

//items that are half in the trolley will not add anyting to this number
int CalculateAreaFilled(TrolleyState *state);

#endif