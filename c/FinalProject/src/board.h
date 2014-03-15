#ifndef BOARD_H_
#define BOARD_H_

#include <stdio.h>

typedef struct board_s {
	int** cells;
	int n;
	int m;
	int (*scoring_func)(int**, int, int);
	int (*make_move)(int**, int, int, int);
} Board;

int board_is_full(board_t board, int m);

#endif /* BOARD_H_ */
