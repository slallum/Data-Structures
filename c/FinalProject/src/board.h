#ifndef BOARD_H_
#define BOARD_H_

#include <stdio.h>

typedef struct board_s {
	int** cells;
	int n;
	int m;
} Board;

typedef struct move_s {
	int i;
	int j;
} Move;

int board_is_full(Board board, int m);

Board *new_board(int n, int m);

Board *copy_board(Board *board);

/**
 * If at least one cell in the board has no value in it,
 * return true - means there are more moves
 */
int board_full(Board* board);

/**
 * Frees each and every dynamic memory allocated for the board
 */
void free_board(Board* board);

#endif /* BOARD_H_ */
