#include "board.h"

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void Board_Reset(Board *self, Player *pPlayer1, Player *pPlayer2)
{
    Cell cell1 = {
        .tag = CELL_PLAYER1,
        .player.kind = KIND_NORMAL,
    };

    Cell cell2 = {
        .tag = CELL_PLAYER2,
        .player.kind = KIND_NORMAL,
    };

    int pieces1 = 0;
    int pieces2 = 0;

    bool is_white = IS_WHITE;
    for (int i = 0; i < 2; ++i)
    {
        for (int j = 0; j < BOARD_SIZE; ++j)
        {
            if (is_white)
            {
                self->matrix[i][j] = cell1;
                pieces1++;
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
                self->matrix[i][j] = cell2;
                pieces2++;
            }

            is_white = !is_white;
        }

        is_white = !is_white;
    }

    assert(pieces1 == pieces2);

    Player_Reset(pPlayer1, pieces1);
    Player_Reset(pPlayer2, pieces2);
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

Point Board_GetCell(Board *self)
{
    char buffer[3]; // 2 caracters + 1 '\0'
    do
    {
        if (scanf("%2s", buffer) == EOF)
        {
            exit(EXIT_FAILURE);
        }

        int c;
        while ((c = getchar()) != '\n' && c != EOF)
        {
        }

        if (strlen(buffer) != 2)
        {
            printf("ERRO. Digite uma 1 letra e 1 número, respectivamente: ");
            continue;
        }

        const char last_char = 'a' + BOARD_SIZE - 1;
        if (buffer[0] < 'a' || buffer[0] > last_char)
        {
            printf("ERRO. O primeiro carácter deve estar entre '%c' e '%c': ", 'a', last_char);
            continue;
        }

        const char last_num = '1' + BOARD_SIZE - 1;
        if (buffer[1] < '1' || buffer[1] > last_num)
        {
            printf("ERRO. O segundo carácter deve estar entre %c e %c: ", '1', last_num);
            continue;
        }

        int line = buffer[0] - 'a';
        int column = buffer[1] - '1';
        Point p = {
            .line = line,
            .column = column,
        };

        if (Board_CellAt(self, p).tag == CELL_NONE)
        {
            printf("ERRO. Indique uma peça de um jogador: ");
            continue;
        }

        return p;
    } while (true);
}

void Board_Move(Board *self, Point start)
{
    switch (Board_CellAt(self, start).tag)
    {
    case CELL_PLAYER1:
        break;
    case CELL_PLAYER2:
        break;
    case CELL_NONE:
        printf("ERRO. Não pode ser uma célula vazia");
        exit(EXIT_FAILURE);
        break;
    }
}

Cell Board_CellAt(Board *self, Point p)
{
    assert(p.line >= 0 && p.line < BOARD_SIZE);
    assert(p.column >= 0 && p.column < BOARD_SIZE);

    return self->matrix[p.line][p.column];
}
