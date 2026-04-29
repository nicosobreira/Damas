#pragma once

#include "board.h"

typedef struct Game
{
    Board board;
    bool is_player1;
} Game;

Game Game_New(void);
void Game_Reset(Game *self);

void Game_Intro(void);

void Game_Loop(Game *self);

void Game_Input(Game *self);
void Game_Update(Game *self);
void Game_Draw(Game *self);
