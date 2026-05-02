#pragma once

#include "cell.h"
#include "player.h"

#define BOARD_SIZE (8)

typedef struct PieceAt
{
    int line;
    int column;
} PieceAt;

typedef struct Board
{
    Cell matrix[BOARD_SIZE][BOARD_SIZE];
    int player1;
    int player2;
} Board;

/// Creates a new empty board
Board Board_New(void);

void Board_Reset(Board *self, Player *pPlayer1, Player *pPlayer2);

void Board_Draw(Board *self);

void Board_DrawTopHeader(Board *self);

PieceAt Board_SelectPiece(Board *self, Player *player);

bool Board_MovePiece(PieceAt *pTo, Board *self, Player *player, PieceAt from);

Cell Board_CellAt(Board *self, PieceAt p);
