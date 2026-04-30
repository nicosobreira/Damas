#pragma once

#include "cell.h"
#include "player.h"

#define BOARD_SIZE (8)

typedef struct Point
{
    int line;
    int column;
} Point;

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

Point Board_GetCell(Board *self);

void Board_Move(Board *self, Point p);

Cell Board_CellAt(Board *self, Point p);
