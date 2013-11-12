/*
 * game.c
 *
 *  Created on: Nov 12, 2013
 *      Author: shir
 */

#include <game.h>
#include <board.h>

void play_game() {

	Game game = {.is_comp_turn=0, .board=request_board(), .turn_counter=1};
	Move current_move;
	while (!is_empty_board(game.board)) {
		print_game_status(game);
		if (game.is_comp_turn == 1) {
			current_move = calculate_next_best_move(game.board);
			print_move(current_move, 1);
		} else {
			print_board(game.board);
			current_move = request_move(game.board);
		}
		make_move(current_move);
		game.turn_counter++;
		game.is_comp_turn = !game.is_comp_turn;
	}
	print_winner(game);
}
