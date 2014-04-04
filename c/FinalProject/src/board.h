#ifndef BOARD_H_
#define BOARD_H_

#include <stdio.h>

typedef struct board_s {
	int** cells;
	int n;
	int m;
	// int (*scoring_func)(int**, int, int);
	// int (*make_move)(int**, int, int, int);
} Board;

typedef struct move_s {
	int i;
	int j;
} Move;

int board_is_full(Board board, int m);

Board *new_board(int n, int m);

#endif /* BOARD_H_ */
