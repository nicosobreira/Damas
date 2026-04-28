#include "board.h"

#include <stddef.h>
#include <stdio.h>

Board Board_New(void)
{
	Board board;

	for (int i = 0; i < BOARD_SIZE; ++i)
	{
		for (int j = 0; j < BOARD_SIZE; j += 2)
		{
			board.matrix[i][j].tag = CELL_BLACK;
			board.matrix[i][j + 1].tag = CELL_WHITE;
		}
	}

	return board;
}

void Board_Reset(Board *self)
{
	Cell player1 = {
		.tag = CELL_PLAYER1,
		.data.player1 = KIND_NORMAL,
	};

	Cell player2 = {
		.tag = CELL_PLAYER1,
		.data.player2 = KIND_NORMAL,
	};

	int black = 0;
	for (int i = 0; i < 3; ++i)
	{
		for (int j = black; j < BOARD_SIZE - black; j += i)
		{
			self->matrix[i][j] = player1;
		}

		if (black == 0)
		{
			black = 1;
		}
		else
		{
			black = 0;
		}
	}

}

void Board_Draw(Board *self)
{
	bool is_black = true;

	for (size_t i = 0; i < BOARD_SIZE; ++i)
	{
		for (size_t j = 0; j < BOARD_SIZE; ++j)
		{
			Cell cell = self->matrix[i][j];

			switch (cell.tag)
			{
				case CELL_PLAYER1: 
					printf("\e[41m  \e[0m");
					break;
				case CELL_PLAYER2:
					printf("\e[43m  \e[0m");
					break;
				case CELL_BLACK:
					printf("\e[40m  \e[0m");
					break;
				case CELL_WHITE:
					printf("\e[47m  \e[0m");
					break;
			}

			is_black = !is_black;
		}

		printf("\n");
		is_black = !is_black;
	}
}
