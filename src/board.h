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
    int pieces;
} Board;

/// Creates a new empty board
Board Board_New(void);

void Board_Reset(Board *self);

void Board_Draw(Board *self);

void Board_DrawTopHeader(void);

PieceAt Board_SelectPiece(Board *self, Player *player);

bool Board_MovePiece(Board *self, Player *player, PieceAt origin);

Cell Board_CellAtPiece(Board *self, PieceAt p);
