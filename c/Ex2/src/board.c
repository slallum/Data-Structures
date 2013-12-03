/*
 * board.c
 *
 *  Created on: Nov 12, 2013
 *      Author: shir
 */

#include "board.h"

/**
 * Read the board parameters from the user.
 * Validation:
 *  - Num of heaps > 32 or < 1 fails the request.
 *  - Any of the heaps has a non-positive size
 */
Board* request_board() {

	int num_of_heaps;
	int *heaps;
	int i;

	printf("Enter the number of heaps:\n");
	scanf("%d", &num_of_heaps);
	if ((num_of_heaps < 1) || (num_of_heaps > 32)) {
		printf("Error: the number of heaps must be between 1 and 32.\n");
		return NULL;
	}
	heaps = (int*) calloc(num_of_heaps, sizeof(int));
	printf("Enter the heap sizes:\n");
	for (i = 0; i < num_of_heaps; i++) {
		scanf("%d", &heaps[i]);
		if (heaps[i] < 0) {
			printf("Error: the size of heap %d should be positive.\n", i  + 1);
			return NULL;
		}
	}
	Board* board = (Board*) malloc(sizeof(Board));
	board->num_of_heaps = num_of_heaps;
	board->heaps = heaps;
	return board;
}

/**
 * Go over all of heaps - if any of their sizes is not 0, return false
 */
int is_board_empty(Board* current_board) {
	int i;

	for (i = 0; i < current_board->num_of_heaps; i++) {
		if (current_board->heaps[i] != 0) {
			return 0;
		}
	}
	return 1;
}

/**
 * Prints the contents of all the stacks in the form of
 * a pile of stars representing each object
 */
void print_board(Board* current_board) {
	int max_heap_size = 0;
	int i, level;

	// Find max size in order to know how many lines needed to be printed
	for (i = 0; i < current_board->num_of_heaps; i++) {
		if (current_board->heaps[i] > max_heap_size) {
			max_heap_size = current_board->heaps[i];
		}
	}

	// print heaps
	for (level = max_heap_size; level > 0 ; level--) {
		// first - print " " or "*" according to the first heap
		if (current_board->heaps[0] >= level) printf("*");
		else printf(" ");
		// now for the tabs and other spaces/*
		for (i = 1; i < current_board->num_of_heaps; i++) {
			printf("\t");
			if (current_board->heaps[i] >= level) printf("*");
			else printf(" ");
		}
		printf("\n");
	}
}
