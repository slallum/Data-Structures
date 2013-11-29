/*
 * board.c
 *
 *  Created on: Nov 12, 2013
 *      Author: shir
 */

#include <stdio.h>

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
	num_of_heaps = scanf("%d", &num_of_heaps);
	if ((num_of_heaps < 1) || (num_of_heaps > 32)) {
		printf("Error: the number of heaps must be between 1 and 32.\n");
		return NULL;
	}
	*heaps = (int*) malloc(num_of_heaps);
	printf("Enter the heap sizes:\n");
	for (i = 0; i < num_of_heaps; i++) {
		scanf("%d", heaps + i);
		if (*(heaps + i) < 0) {
			printf("Error: the size of heap (%d) should be positive.\n", i);
		}
	}
	return &(Board){.num_of_heaps=num_of_heaps, .heaps=heaps};
}

/**
 * Go over all of heaps - if any of their sizes is not 0, return false
 */
int is_board_empty(Board current_board) {

	int i;

	for (i = 0; i < current_board.num_of_heaps; i++) {
		if (sizeof(current_board.heaps[i]) != 0) {
			return 0;
		}
	}
	return 1;
}

void print_board(Board* current_board) {

	int max_heap_size = 0;
	int i, j;
	char heap_separator;
	char level_separator;
	// Find max size in order to know how many lines needed to be printed
	for (i = 0; i < current_board->num_of_heaps; i++) {
		if (*(current_board->heaps + i) > max_heap_size) {
			max_heap_size = *(current_board->heaps + i);
		}
	}
	// Print heaps
	for (i = 0; i < max_heap_size; i++) {
		printf("%c", level_separator);
		for (j = 0; j < current_board->num_of_heaps; j++) {
			if (*(current_board->heaps + j) - i > 0) {
				printf("%c*", heap_separator);
			}
			heap_separator = '\t';
		}
		level_separator = '\n';
	}
}
