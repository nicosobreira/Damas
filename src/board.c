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

    board.pieces = 0;

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
    for (int i = BOARD_SIZE - 1; i > BOARD_SIZE - 3; --i)
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

    self->pieces = pieces1;
}

void Board_Draw(Board *self)
{
    bool is_white = IS_WHITE;

    printf("  ");
    Board_DrawTopHeader();

    for (int i = 0; i < BOARD_SIZE; ++i)
    {
        printf("%c ", 'a' + i);

        for (int j = 0; j < BOARD_SIZE; ++j)
        {
            Cell cell = self->matrix[i][j];

            Cell_Draw(cell, is_white);

            is_white = !is_white;
        }

        printf(" %c", 'a' + i);

        printf("\n");
        is_white = !is_white;
    }

    printf("  ");
    Board_DrawTopHeader();
}

void Board_DrawTopHeader(void)
{
    for (int j = 0; j < BOARD_SIZE; ++j)
    {
        printf("%d ", j + 1);
    }

    printf("\n");
}

static bool getAt(PieceAt *p, char digit, char letter)
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

        if (!getAt(&from, buffer[0], buffer[1]))
        {
            continue;
        }

        if (Board_CellAtPiece(self, from).tag == CELL_NONE)
        {
            printf(" escolha uma peça sua: ");
            continue;
        }

        if (Board_CellAtPiece(self, from).tag != player->tag)
        {
            printf(" escolha uma peça do %s: ", player->name);
            continue;
        }

        return from;
    } while (true);
}

bool Board_MovePiece(Board *self, Player *player, PieceAt origin)
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

        PieceAt target = {0};

        if (!getAt(&target, buffer[0], buffer[1]))
        {
            continue;
        }

        CellTag tag = Board_CellAtPiece(self, target).tag;

        Cell empty = {
            .tag = CELL_NONE,
        };

        Cell p = self->matrix[origin.line][origin.column];

        if (tag == CELL_NONE)
        {
            self->matrix[origin.line][origin.column] = empty;
            self->matrix[target.line][target.column] = p;
        }
        else if (tag != player->tag)
        {
            PieceAt final = {
                .line = target.line + (target.line - origin.line),
                .column = target.column + (target.column - origin.column),
            };

            self->matrix[origin.line][origin.column] = empty;
            self->matrix[target.line][target.column] = empty;
            self->matrix[final.line][final.column] = p;

            player->pieces++;
        }
        else
        {
            printf(" selecione outra peça: ");
            continue;
        }

        return true;
    } while (true);
}

Cell Board_CellAtPiece(Board *self, PieceAt p)
{
    return self->matrix[p.line][p.column];
}
