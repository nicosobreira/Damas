#pragma once

typedef enum Kind {
	KIND_NORMAL,
	KIND_DAMA,
} Kind;

typedef enum CellTag {
	CELL_PLAYER1,
	CELL_PLAYER2,
	CELL_BLACK,
	CELL_WHITE,
} CellTag;

typedef struct Cell {
	CellTag tag;
	union {
		Kind player1;
		Kind player2;
	} data;
} Cell;

