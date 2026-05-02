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

static bool getAt(PieceAt *p, Board *self, char digit, char letter)
{
    const char last_num = '1' + BOARD_SIZE - 1;
    if (digit < '1' || digit > last_num)
    {
        printf(" o primeiro carácter deve estar entre %c e %c: ", '1', last_num);
        return false;
    }

    const char last_char = 'a' + BOARD_SIZE - 1;
    if (letter < 'a' || letter > last_char)
    {
        printf(" o segundo carácter deve estar entre %c e %c: ", 'a', last_char);
        return false;
    }

    int line = letter - 'a';
    int column = digit - '1';

    assert(line >= 0 && line < BOARD_SIZE);
    assert(column >= 0 && column < BOARD_SIZE);

    p->line = line;
    p->column = column;

    return true;
}

PieceAt Board_SelectPiece(Board *self, Player *player)
{
    char buffer[3]; // 2 caracters + '\0'
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
            printf(" digite uma coordenada: ");
            continue;
        }

        PieceAt from = {0};

        if (!getAt(&from, self, buffer[0], buffer[1]))
        {
            continue;
        }

        if (Board_CellAt(self, from).tag == CELL_NONE)
        {
            printf(" escolha uma peça sua: ");
            continue;
        }

        if (Board_CellAt(self, from).tag != player->tag)
        {
            printf(" escolha uma peça do %s: ", player->name);
            continue;
        }

        return from;
    } while (true);
}

bool Board_MovePiece(PieceAt *pTo, Board *self, Player *player, PieceAt from)
{
    char buffer[3]; // 2 caracters + '\0'
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

        if (buffer[0] == 'r')
        {
            return false;
        }

        if (strlen(buffer) != 2)
        {
            printf(" digite uma coordenada: ");
            continue;
        }

        PieceAt to = {0};

        if (!getAt(&to, self, buffer[0], buffer[1]))
        {
            continue;
        }

        if (Board_CellAt(self, to).tag != CELL_NONE)
        {
            printf(" selecione um espaço vazio: ");
            continue;
        }

        switch (player->direction)
        {
        case DIRECTION_DOWN:
            break;
        case DIRECTION_UP:
            break;
        }

        *pTo = to;

        return true;
    } while (true);
}

Cell Board_CellAt(Board *self, PieceAt p)
{
    return self->matrix[p.line][p.column];
}
