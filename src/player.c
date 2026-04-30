#include "player.h"

#include <stdio.h>

Player Player_New(const char *name, Color color)
{
    return (Player){
        .pieces = 0,
        .name = name,
        .color = color,
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
