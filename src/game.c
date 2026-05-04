#include "game.h"

#include <stdio.h>

#include "color.h"

// Gerar uma lista de indicíces de movimentação valida

// TODO: Criar uma matrix de overlay pra a seleção de uma peça

static void clearScreen(void)
{
	printf(CLEAR_SCREEN RESET_CURSOR);
}

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
    Player player1 = Player_New("Jogador 1", FG_RED, BG_RED, CELL_PLAYER1);
    Player player2 = Player_New("Jogador 2", FG_BLUE, BG_BLUE, CELL_PLAYER2);

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
    printf("Formato da coordenada: 1a, ou seja, linha 'a' e coluna '1'.\n");
    printf("Depois, digite para a onde quer mover.\n");
    printf("Você pode voltar para o passo anterior ao apertar 'r'\n");

    printf("\n");

    subtitle("Comer peça");

    printf("Move dentro de uma peça para come-la. O pulo é automático.\n");

    printf("\n");
}

void Game_Reset(Game *self)
{
    Board *pBoard = &self->board;

    Board_Reset(pBoard);

    self->pCurrent = &self->player1;
}

void Game_Loop(Game *self)
{
    Game_Reset(self);

    Game_Intro();

    while (self->isRunning)
    {
        Game_Draw(self);

        Game_Input(self);

		clearScreen();
    }
}

void Game_Input(Game *self)
{
    do
    {
        Player_DrawName(self->pCurrent);
        printf(" escolha uma peça para mover: ");
        PieceAt origin = Board_SelectPiece(&self->board, self->pCurrent);

        Player_DrawName(self->pCurrent);
        printf(" para onde quer mover? (r para voltar) ");

        // TODO: Criar uma função para mostrar os passos disponíveis, se não
        // houver nenhum, volte para a seleção

        bool result = Board_MovePiece(&self->board, self->pCurrent, origin);
        if (result)
        {
            break;
        }
    } while (true);

    if (self->pCurrent->pieces == self->board.pieces)
    {
		printf("Parabéns! O ");
		Player_DrawName(self->pCurrent);
		printf(" ganhou!");

        self->isRunning = false;
		return;
    }

    if (self->pCurrent == &self->player1)
    {
        self->pCurrent = &self->player2;
    }
    else
    {
        self->pCurrent = &self->player1;
    }
}

void Game_Draw(Game *self)
{
	Player_DrawScore(&self->player1);
	Player_DrawScore(&self->player2);

    Board_Draw(&self->board);
}
