#include "game.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "color.h"

// Gerar uma lista de indicíces de movimentação valida

static void line(const char *f)
{
    const int size = 20;

    for (int i = 1; i <= size; ++i)
    {
        printf("%s", f);
    }

    printf("\n");
}

static void title(const char *t)
{
    line("=");
    printf("%s\n", t);
    line("=");
}

static void subtitle(const char *t)
{
    printf("%s\n", t);
    line("=");
}

Game Game_New(void)
{
    Player player1 = Player_New("Jogador 1", FG_RED);
    Player player2 = Player_New("Jogador 2", FG_BLUE);

    Board board = Board_New();

    return (Game){
        .board = board,
        .player1 = player1,
        .player2 = player2,
        .isRunning = true,
    };
}

void Game_Intro(void)
{
    title("Jogo da Dama");

    printf("\n");

    subtitle("O Tabuleiro");

    printf("As peças " BG_RED "  " RESET " são do " FG_RED "Jogador 1" RESET "\n");
    printf("As peças " BG_BLUE "  " RESET " são do " FG_BLUE "Jogador 2" RESET "\n");
    printf("Os espaços " BG_WHITE "  " RESET " estão disponíveis para a movimentação\n");

    printf("\n");

    subtitle("Movimentação");

    printf("Quando for sua vez, selecione a peça que quer mover digitando sua coordenada\n");
    printf("Formato da coordenada: a1, ou seja, linha 'a' e coluna '1'.\n");
    printf("Depois, digite para a onde quer mover.\n");
    printf("Você pode voltar para o passo anterior ao apertar 'r'\n");

    printf("\n");
}

void Game_Reset(Game *self)
{
    Board *pBoard = &self->board;

    Board_Reset(pBoard, &self->player1, &self->player2);

    self->pCurrent = &self->player1;
}

void Game_Loop(Game *self)
{
    Game_Intro();

    Game_Reset(self);

    while (self->isRunning)
    {
        Game_Draw(self);

        Game_Input(self);

        Game_Update(self);
    }
}

void Game_Input(Game *self)
{
    Player_PrintName(self->pCurrent);
    printf(" escolha uma peça para mover: ");

    Point p = Board_GetCell(&self->board);

    printf("line = %d\n", p.line);
    printf("column = %d\n", p.column);

    if (self->pCurrent == &self->player1)
    {
        self->pCurrent = &self->player2;
    }
    else
    {
        self->pCurrent = &self->player1;
    }
}

void Game_Update(Game *self)
{
}

void Game_Draw(Game *self)
{
    Board *pBoard = &self->board;

    Board_Draw(pBoard);
}
