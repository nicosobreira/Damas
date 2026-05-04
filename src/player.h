#pragma once

#include "cell.h"
#include "color.h"

typedef struct Player
{
    const char *name;
    const Color color_fg;
    const Color color_bg;
    const CellTag tag;

    int pieces;
} Player;

Player Player_New(const char *name, Color fg, Color bg, CellTag tag);

void Player_Reset(Player *self, int pieces);

void Player_DrawName(Player *self);

void Player_DrawScore(Player *self);
