#pragma once

#include "board.h"
#include "player.h"

typedef struct Piece
{
    int line;
    int column;
} Piece;

typedef struct Movement
{
    Piece origin;
    Piece target;
} Movement;

Movement Movement_Get(Board *board, Player *player);

Piece Movement_GetOrigin(Board *board, Player *player);

Piece Movement_GetTarget(Board *board, Player *player);
