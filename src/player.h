#pragma once

#include "color.h"

typedef struct Player
{
    const char *name;
    Color color;
    int pieces;
} Player;

Player Player_New(const char *name, Color color);

void Player_Reset(Player *self, int pieces);

void Player_PrintName(Player *self);
