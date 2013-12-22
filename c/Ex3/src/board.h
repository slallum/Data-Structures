#ifndef BOARD_H_
#define BOARD_H_

#include <stdio.h>

typedef struct Board {
	int** cells;
	int n;
	int m;
	int (*scoring_func)(int**, int, int);
	int (*make_move)(int**, int, int);
} board_t;

/**
 * Prints the board's current state
 */
void print_board(board_t* board);

/**
 * Calculates score for board's current state
 * according to given scoring function
 */
int get_score(board_t* board);

int execute_move(board_t* board, int i, int value);


#endif /* BOARD_H_ */
