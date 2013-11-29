/*
 * main.c
 *
 *  Created on: Nov 12, 2013
 *      Author: shir
 */

#include "nim.h"
#include "ai_nim.h"

int main() {
	play_game();
	return 0;
}

void play_game() {

	Game game = {.is_comp_turn=0, .board=request_board(), .turn_counter=1};
	if (game.board == 0) {
		return;
	}
	Move* current_move = &(Move){.heap_num=NULL, .num_of_objects=NULL};
	while (!(is_board_empty(game.board) == 1)) {
		print_game_status(&game);
		if (game.is_comp_turn == 1) {
			*current_move = calculate_next_best_move(*game.board);
			print_move(current_move, 1);
		} else {
			print_board(game.board);
			request_move(current_move, game.board);
		}
		make_move(game.board, current_move);
		game.turn_counter++;
		game.is_comp_turn = !game.is_comp_turn;
	}
	print_winner(&game);
	free(game.board->heaps);
}

