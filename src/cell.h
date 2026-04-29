#pragma once

#include <stdbool.h>

#include "color.h"

typedef enum Kind
{
    KIND_NORMAL,
    KIND_DAMA,
} Kind;

typedef enum CellTag
{
    CELL_PLAYER1,
    CELL_PLAYER2,
    CELL_NONE,
} CellTag;

typedef struct Cell
{
    CellTag tag;
    union {
        Kind kind;
    } player;
} Cell;

void Cell_Draw(Cell self, bool is_black);

void Cell_DrawPlayer(Cell self, Color normal);
