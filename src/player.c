#include "player.h"

#include <stdio.h>

Player Player_New(const char *name, Color fg, Color bg, CellTag tag)
{
    return (Player){
        .name = name,
        .color_fg = fg,
        .color_bg = bg,
        .tag = tag,
        .pieces = 0,
    };
}

void Player_Reset(Player *self, int pieces)
{
    self->pieces = pieces;
}

void Player_DrawName(Player *self)
{
    printf("%s%s" RESET, self->color_fg, self->name);
}

void Player_DrawScore(Player *self)
{
    printf("Comidas de ");
    Player_DrawName(self);
    printf(": %d\n", self->pieces);
}
