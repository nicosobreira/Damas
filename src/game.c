#include "game.h"

#include <stdio.h>
#include <stdlib.h>

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

Game Game_New(void)
{
    Board board = Board_New();
    Board_Reset(&board);

    return (Game){
        .board = board,
        .is_player1 = true,
    };
}

void Game_Intro(void)
{
    title("Jogo da Dama");

    printf("\n");

    printf("O Tabuleiro\n");
    line("=");

    printf("As peças " BG_RED "  " RESET " são do " FG_RED "Jogador 1" RESET "\n");
    printf("As peças " BG_BLUE "  " RESET " são do " FG_BLUE "Jogador 2" RESET "\n");
    printf("Os espaços " BG_WHITE "  " RESET " estão disponíveis para a movimentação\n");

    printf("\n");

    printf("Movimentação\n");
    line("=");

    printf("Quando for sua vez, selecione a peça que quer mover digitando sua coordenada.\n");
    printf("Depois, digite para a onde quer mover.\n");
    printf("Você pode voltar para o passo anterior ao apertar 'r'\n");

    printf("\n");
}

void Game_Reset(Game *self)
{
    Board *pBoard = &self->board;

    Board_Reset(pBoard);

    self->is_player1 = true;
}

void Game_Loop(Game *self)
{
    Game_Intro();

    Game_Draw(self);

    Game_Input(self);

    Game_Update(self);
}

void Game_Input(Game *self)
{
    char buffer[3]; // 2 caracters + 1 '\0'

    printf("Faça: ");
    if (scanf("%2s", buffer) == EOF)
    {
        exit(EXIT_FAILURE);
    }

    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
    }

    printf("buffer: %s\n", buffer);

    self->is_player1 = !self->is_player1;
}

void Game_Update(Game *self)
{
}

void Game_Draw(Game *self)
{
    Board *pBoard = &self->board;

    Board_Draw(pBoard);
}
