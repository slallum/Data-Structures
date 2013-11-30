/*
 * game.c
 *
 *  Created on: Nov 12, 2013
 *      Author: shir
 */
#include <stdio.h>

#include "game.h"

/**
 * Ask user for a move to make on the board and check it is
 * actually valid according to current status of the board
 * (that heap exists and has at least amount of objects required to remove)
 * As long as move is not legal, requests another one.
 */
void request_move(Move* current_move, Board* current_board) {

	int heap_num, objects_num;
	int valid = 0;

	printf("Your turn: please enter the heap index and the number of removed objects.\n");
	while (!valid) {
		scanf("%d", &heap_num);
		scanf("%d", &objects_num);
		valid = checkValidity(current_board, &heap_num, &objects_num);
		if (!valid) {
			printf("%s", "Error: Invalid input.\nPlease enter again the heap index and the number of removed objects.\n");
		}
	}
	current_move->heap_num = &heap_num;
	current_move->num_of_objects = &objects_num;
}

/**
 * Checks if user's request for moving objects from heap is acceptable for the
 * current state of the board.
 */
int checkValidity(Board* current_board, int heap_num, int objects_num) {
	int* heaps = current_board->heaps;
	if (heap_num > current_board->num_of_heaps) {
		return 0;
	}
	if (heaps[heap_num - 1] < objects_num) {
		return 0;
	}
	return 1;
}

/**
 * Performs the move as requested - actually reduces the number of objects
 * in the requested heap by the requested amount.
 */
void make_move(Board* current_board, Move* requested_move) {

	*(current_board->heaps + *(requested_move->heap_num)) -= *(requested_move->num_of_objects);
}

/**
 * Prints details of the move to the user
 */
void print_move(Move* move, int is_comp_turn) {
	if (is_comp_turn) {
		printf("Computer takes ");
	} else {
		printf("You take ");
	}
	printf("%d objects from heap %d.\n", *(move->num_of_objects), *(move->heap_num));
}

/**
 * Prints current status of the game
 */
void print_game_status(Game* game) {
	int i;
	int *heaps = game->board->heaps;

	printf("In turn %d heap sizes are:", game->turn_counter);
	for (i = 0; i < game->board->num_of_heaps; i++) {
		printf(" h%d=%d", i + 1, heaps[i]);
	}
	printf(".\n");
}

/**
 * Prints who won the game
 */
void print_winner(Game* game) {
	if (game->is_comp_turn) {
		printf("You win!");
	} else {
		printf("Computer wins!");
	}
}

