/*
 * reversi_brain.c
 *
 *  Created on: Apr 10, 2014
 *      Author: shir
 */


#include "reversi_brain.h"

Game *reversi_new_game() {
	Game *game = (Game*) malloc(sizeof(Game));
	if (game == NULL) {
		printf("ERROR: game could not be initialized.");
		return NULL;
	}

	game->save_game_name = REVERSI_NAME;
	game->board = new_board(REVERSI_BOARD_N, REVERSI_BOARD_M);
	game->is_first_players_turn = FIRST_PL_TURN;
	reversi_init_board(game->board);

	game->first_player_ai = NO_PLAYER;
	game->second_player_ai = NO_PLAYER;
	game->depth_range[0] = 1;
	game->depth_range[1] = 4;
	game->first_player_depth = game->depth_range[0];
	game->second_player_depth = game->depth_range[0];

	game->game_over = 0;

	game->make_move = reversi_make_move;
	game->won_game = reversi_won_game;
	game->init_board = reversi_init_board;

//	game->tree = create_tree(game->board, game->depth, reversi_make_move, reversi_get_score);

	game->tiles[0] = RN_IMG;
	game->tiles[1] = RW_IMG;
	game->tiles[2] = RB_IMG;

	return game;
}

/**
 * Adds to the board 4 middle tiles that open the game
 */
void reversi_init_board(Board* board) {
	int i, j;
	int player = FIRST_PL_TURN;
	for (i = (REVERSI_BOARD_N / 2) - 1; i <= REVERSI_BOARD_N / 2; i++) {
		for (j = (REVERSI_BOARD_M / 2) - 1; j <= REVERSI_BOARD_M / 2; j++) {
			board->cells[i][j] = player;
			player *= (SECOND_PL_TURN);
		}
		player *= (SECOND_PL_TURN);
	}
}

/*
 *
 */
int reversi_make_move(Board* board, Move* new_move, int value) {
	int oppAdjacent = 0;
	int i, j;
	int directions[3] = {-1, 0, 1};
	Move* current_dir = (Move*) malloc(sizeof(Move));

	// Requested cell is taken
	if (board->cells[new_move->i][new_move->j] != 0) {
		return -1;
	}
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			// Check all except no move in no direction
			if ((i != 1) || (j != 1)) {
				current_dir->i = directions[i];
				current_dir->j = directions[j];
				oppAdjacent = consider_move(board, new_move, current_dir, value) || oppAdjacent;
			}
		}
	}
	free(current_dir);
	// Move without adjacent opponent tiles is not legal
	if (!oppAdjacent) {
		return -1;
	}
	return 0;
}

/**
 *
 * @param board		Current board of the game, for checking
 * @param position	Current position for checking
 * @param direction	To move for checking validity - can have the values 1, -1, 0
 * 					as it's i / j, to indicate up, down, left, right
 */
int consider_move(Board* board, Move* position, Move* direction, int value) {

	int i = position->i + direction->i;
	int j = position->j + direction->j;

	if ((i < 0) || (j < 0) || (i >= REVERSI_BOARD_N) || (j >= REVERSI_BOARD_M)) {
		return 0;
	}
	if (board->cells[i][j] == value * SECOND_PL_TURN) {
		// Explore through board according to requested direction
		while ((i + direction->i >= 0) && (i + direction->i < REVERSI_BOARD_N) &&
				(j + direction->j >= 0) && ( j + direction->j < REVERSI_BOARD_M) &&
				(board->cells[i][j] == value * SECOND_PL_TURN)) {
			i += direction->i;
			j += direction->j;
		}
		// Move is valid if reached tile of original value
		if (board->cells[i][j] == value) {
			// Go back and flip all tiles
			while ((i != position->i) || (j != position->j)) {
				i -= direction->i;
				j -= direction->j;
				board->cells[i][j] = value;
			}
			return 1;
		}
	}
	return 0;
}

/*
 * Checks if the board has a winning streak.
 * Counts tiles of each player in order to determine which player won.
 * Changes current player to be the winner.
 *
 */
Move** reversi_won_game(Game* game) {
	int first_count = 0;
	int second_count = 0;
	int i, j;
	Move** winning_span = { NULL };

	if (board_full(game->board) || (no_moves(game, FIRST_PL_TURN)
			&& no_moves(game, SECOND_PL_TURN))) {
		for (i = 0; i < game->board->n; i++) {
			for (j = 0; j < game->board->m; j++) {
				if (game->board->cells[i][j] == FIRST_PL_TURN) {
					first_count++;
				}
				if (game->board->cells[i][j] == SECOND_PL_TURN) {
					second_count++;
				}
			}
		}
		if (first_count == second_count) {
			game->is_first_players_turn = 0;
		}
		if (first_count > second_count) {
			game->is_first_players_turn = FIRST_PL_TURN;
		} else {
			game->is_first_players_turn = SECOND_PL_TURN;
		}
		game->game_over = 1;
		return winning_span;
	}
	return NULL;
}

/**
 *
 */
int reversi_get_score(Board* board) {


}



