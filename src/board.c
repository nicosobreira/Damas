#include "board.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

static const bool IS_WHITE = true;

Board Board_New(void)
{
    Board board;

    for (int i = 0; i < BOARD_SIZE; ++i)
    {
        for (int j = 0; j < BOARD_SIZE; ++j)
        {
            board.matrix[i][j].tag = CELL_NONE;
        }
    }

    return board;
}

void Board_Reset(Board *self)
{
    Cell player1 = {
        .tag = CELL_PLAYER1,
        .player.kind = KIND_NORMAL,
    };

    Cell player2 = {
        .tag = CELL_PLAYER2,
        .player.kind = KIND_NORMAL,
    };

    bool is_white = IS_WHITE;
    for (int i = 0; i < 2; ++i)
    {
        for (int j = 0; j < BOARD_SIZE; ++j)
        {
            if (is_white)
            {
                self->matrix[i][j] = player1;
            }

            is_white = !is_white;
        }

        is_white = !is_white;
    }

    is_white = !IS_WHITE;
    for (int i = BOARD_SIZE - 1; i > 5; --i)
    {
        for (int j = 0; j < BOARD_SIZE; ++j)
        {
            if (is_white)
            {
                self->matrix[i][j] = player2;
            }

            is_white = !is_white;
        }

        is_white = !is_white;
    }
}

void Board_Draw(Board *self)
{
    bool is_white = IS_WHITE;

    printf("  ");
    Board_DrawTopHeader(self);

    for (int i = 0; i < BOARD_SIZE; ++i)
    {
        printf("%c ", 'a' + i);

        for (int j = 0; j < BOARD_SIZE; ++j)
        {
            Cell cell = self->matrix[i][j];

            Cell_Draw(cell, is_white);

            is_white = !is_white;
        }

        printf("\n");
        is_white = !is_white;
    }
}

void Board_DrawTopHeader(Board *self)
{
    for (int j = 0; j < BOARD_SIZE; ++j)
    {
        printf("%d ", j + 1);
    }

    printf("\n");
}
