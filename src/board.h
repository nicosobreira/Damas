#pragma once

#include "cell.h"

#define BOARD_SIZE (8)

typedef struct Board
{
    Cell matrix[BOARD_SIZE][BOARD_SIZE];
    int player1;
    int player2;
} Board;

/// Creates a new empty board
Board Board_New(void);

void Board_Reset(Board *self);

void Board_Draw(Board *self);

void Board_DrawTopHeader(Board *self);
