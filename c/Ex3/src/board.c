/*
 * board.c
 *
 *  Created on: Dec 17, 2013
 *      Author: shir
 */

#include "board.h"

/**
 * Prints the board's current state
 */
void print_board(board_t *board) {
	int i, j;
	for (i = 0; i < board->n; i++) {
		printf("|");
		// Print the data
		for (j = 0; j < board->m; j++) {
			if (board->cells[i][j] == -1) {
				printf(" %c", COMPUTERR_SYMBOL);
			} else if (board->cells[i][j] == 1) {
				printf(" %c", PLAYER_SYMBOL);
			} else {
				printf("  ");
			}
		}
		printf(" |\n");
	}
	// Add dashes line
	for (i = 0; i < DASHES_COUNT; i++) {
		printf("-");
	}
	printf("\n  ");
	// Add coloumn numbering
	for (i = 1; i <= board->m; i++) {
		printf("%d ", i);
	}
	printf(" \n");
}

/**
 * Calculates score for board's current state
 * according to given scoring function
 */
int get_score(board_t *board) {
	return (*board->scoring_func)(board->cells, board->n, board->m);
}

int execute_move(board_t* board, int n, int i, int value) {
	return (*board->make_move)(board->cells, n, i, value);
}

/*
 * checks weather board is full or not
 */
int board_is_full(board_t board, int m) {
	int i;
	for (i=0; i<m; i++) {
		if (board.cells[0][i] == 0) {
			return 0;
		}
	}
	return 1;
}