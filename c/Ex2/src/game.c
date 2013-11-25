/*
 * game.c
 *
 *  Created on: Nov 12, 2013
 *      Author: shir
 */

#include <game.h>
#include <board.h>

int main() {
	play_game();
}

void play_game() {

	Game game = {.is_comp_turn=0, .board=request_board(), .turn_counter=1};
	if (game.board == 0) {
		return;
	}
	Move* current_move;
	while (!is_empty_board(&game.board)) {
		print_game_status(game);
		if (game.is_comp_turn == 1) {
			current_move = calculate_next_best_move(&game.board);
			print_move(current_move, 1);
		} else {
			print_board(&game.board);
			current_move = request_move(&game.board);
		}
		make_move(current_move);
		game.turn_counter++;
		game.is_comp_turn = !game.is_comp_turn;
	}
	print_winner(game);
	free(game.board.heaps);
}

Move* request_move(Board* current_board) {

	int* heap_num, objects_num;
	int valid = 0;
	char* message;
	printf("Your turn: please enter the heap index and the number of removed objects.\n");
	while (!valid) {
		printf(message);
		scanf("%d", heap_num);
		scanf("%d", objects_num);
		valid = valid && checkValidity(current_board, heap_num, objects_num);
		message = "Error: Invalid input.\nPlease enter again the heap index and the number of removed objects.\n";
	}
	return *(Move){.heap_num=heap_num, .num_of_objects=objects_num};
}

/**
 * Checks if user's request for moving objects from heap is acceptable for the
 * current state of the board.
 */
int checkValidity(Board* current_board, int* heap_num, int* objects_num) {
	if (*heap_num > current_board->num_of_heaps) {
		return 0;
	}
	if (current_board->heaps[(*heap_num) - 1] < *objects_num) {
		return 0;
	}
	return 1;
}

int make_move(Board* current_board, Move* requested_move) {
	return 0;
}
