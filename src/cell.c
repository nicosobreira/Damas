#include "cell.h"

#include <stdio.h>

void Cell_Draw(Cell self, bool is_white)
{
    switch (self.tag)
    {
    case CELL_PLAYER1:
        Cell_DrawPlayer(self, BG_RED);
        break;
    case CELL_PLAYER2:
        Cell_DrawPlayer(self, BG_BLUE);
        break;
    case CELL_NONE:
        if (is_white)
        {
            printf(BG_WHITE "  " RESET);
        }
        else
        {
            printf(BG_BLACK "  " RESET);
        }
        break;
    }
}

void Cell_DrawPlayer(Cell self, Color normal)
{
    if (self.player.kind == KIND_NORMAL)
    {
        printf("%s"
               "  " RESET,
               normal);
    }
    else if (self.player.kind == KIND_DAMA)
    {

        printf("%s"
               "**" RESET,
               normal);
    }
}
