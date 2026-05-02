#include "player.h"

#include <stdio.h>

Player Player_New(const char *name, Color color, CellTag tag, Direction direction)
{
    return (Player){
        .pieces = 0,
        .name = name,
        .color = color,
        .tag = tag,
        .direction = direction,
    };
}

void Player_Reset(Player *self, int pieces)
{
    self->pieces = pieces;
}

void Player_PrintName(Player *self)
{
    printf("%s%s" RESET, self->color, self->name);
}
