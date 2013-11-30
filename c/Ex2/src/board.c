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
	heaps = (int*) calloc(sizeof(int)*num_of_heaps, 0);
	printf("Enter the heap sizes:\n");
	for (i = 0; i < num_of_heaps; i++) {
		scanf("%1d", &heaps[i]);
		if (heaps[i] < 0) {
			printf("Error: the size of heap %d should be positive.\n", i  + 1);
			return NULL;
		}
	}
	return &(Board){.num_of_heaps=num_of_heaps, .heaps=heaps};
}

/**
 * Go over all of heaps - if any of their sizes is not 0, return false
 */
int is_board_empty(Board* current_board) {
	int i;

	for (i = 0; i < current_board->num_of_heaps; i++) {
		if (sizeof(current_board->heaps[i]) != 0) {
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

	int num_of_heaps = current_board->num_of_heaps;
	int max_heap_size = 0;
	int i, j;
	int *heaps = current_board->heaps;
	// Find max size in order to know how many lines needed to be printed
	for (i = 0; i < num_of_heaps; i++) {
		if (heaps[i] > max_heap_size) {
			max_heap_size = heaps[i];
		}
	}
	// Print heaps
	for (i = 0; i < max_heap_size; i++) {
		for (j = 0; j < num_of_heaps; j++) {
			if ((heaps[j] + i) >= max_heap_size) {
				printf("%s", "*\t");
			} else {
				printf("%s", " \t");
			}
		}
		printf("%c", '\n');
	}
}
