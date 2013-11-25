/*
 * board.h
 *
 *  Created on: Nov 12, 2013
 *      Author: shir
 */

#ifndef BOARD_H_
#define BOARD_H_

typedef struct Board {
	int num_of_heaps;
	int *heaps;
} Board;

/**
 * Should ask for parameters and make validation tests
 */
Board* request_board();

/**
 * Print content of board
 */
void print_board(Board* current_board);

/**
 * Checks if all the heaps are empty
 */
int is_board_empty(Board* current_board);

#endif /* BOARD_H_ */
