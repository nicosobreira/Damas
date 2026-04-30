#pragma once

#include "board.h"
#include "player.h"

typedef struct Game
{
    Board board;
    Player player1;
    Player player2;
    Player *pCurrent;

    bool isRunning;
} Game;

Game Game_New(void);
void Game_Reset(Game *self);

void Game_Intro(void);

void Game_Loop(Game *self);

void Game_Input(Game *self);
void Game_Update(Game *self);
void Game_Draw(Game *self);
