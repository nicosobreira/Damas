#include <stdio.h>

#include "board.h"

int main(void)
{
	Board board = Board_New();

	Board_Reset(&board);

	Board_Draw(&board);

	return 0;
}
