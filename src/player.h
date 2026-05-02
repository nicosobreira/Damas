#pragma once

#include "cell.h"
#include "color.h"
#include "direction.h"

typedef struct Player
{
    const char *name;
    const Color color;
    const CellTag tag;
    const Direction direction;

    int pieces;
} Player;

Player Player_New(const char *name, Color color, CellTag tag, Direction direction);

void Player_Reset(Player *self, int pieces);

void Player_PrintName(Player *self);
