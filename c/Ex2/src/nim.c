/*
 * main.c
 *
 *  Created on: Nov 12, 2013
 *      Author: shir
 */

#include "nim.h"

int main() {
	play_game();
	return 0;
}

/**
 * Manages the whole game from building the board until victory
 */
void play_game() {
	Move current_move = (Move){.heap_num=0, .num_of_objects=0};
	Game game = {.is_comp_turn=1, .board=request_board(), .turn_counter=1};

	if (game.board == 0) {
		return;
	}
	while (is_board_empty(game.board) == 0) {
		print_game_status(game);
		if (game.is_comp_turn == 1) {
			current_move = calculate_next_best_move(*game.board);
			// print_move(&current_move, game.is_comp_turn);
		} else {
			print_board(game.board);
			request_move(&current_move, game.board);
		}
		print_move(&current_move, game.is_comp_turn);
		make_move(game.board, &current_move);
		game.turn_counter++;
		game.is_comp_turn = !game.is_comp_turn;
	}
	print_winner(&game);
	free(game.board->heaps);
}

