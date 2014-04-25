#include "game_framework.h"

// get the best move for the current game state, by the minmax algorithm with the current depth
// gets best_move pointer - that is already initialized
void get_best_move(Game *game, Move *best_move) {
	int depth, max;
	depth = game->current_player == FIRST_PL_TURN ? game->first_player_depth : game->second_player_depth;
	max = game->current_player == FIRST_PL_TURN;
	minmax_with_extend(game->tree->root, depth, -EXTREME_VALUE, EXTREME_VALUE, 
					   max, game->board, best_move,
					   game->is_valid_move, game->make_move, game->get_score);
}

// return if the current player is AI or not
int current_player_is_ai(Game *game) {
	if (game->current_player == FIRST_PL_TURN) {
		return game->first_player_ai;
	} else {
		return game->second_player_ai;
	}
}


/**
 * Handles all logic around making a move in the game.
 * Updates the tree for all players and get
 *
 * @return	 0 - All went well, move was made and turn should pass on
 * 			-1 - Move was not made and turn should not pass (was illegal for player)
 * 			 1 - Move was made but current player is AI, so no waiting for user
 *
 */
int handle_move(Game* game, int i, int j) {
	Move* new_move;
	if ((new_move = (Move*) malloc(sizeof(Move))) == NULL) {
		printf("ERROR: Allocating memory for new move in handle_move.\n");
		return 0;
	}

	// get the new move
	// if we know that the current player is AI, we'll get the best move for it with minmax
	if (current_player_is_ai(game)) {
		get_best_move(game, new_move);
	// if it's a human player's turn - then i, j are the real move.
	} else {
		new_move->i = i;
		new_move->j = j;
	}

	// Now new_move should be updated
	if (game->make_move(game->board, new_move, game->current_player) == -1) {
		free(new_move);
		return -1;
	}
	// update the tree according to the new move
	update_tree(game->tree, new_move->j, new_move->i, game->current_player == FIRST_PL_TURN ? game->first_player_depth : game->second_player_depth);

	free(new_move);
	return 0;
}


/**
 * Switches players from current to other (flips marks)
 * If currently playing is an AI player, returns 1,
 * indicating to continue fictive clicking, without waiting for user.
 */
int switch_player(Game* game) {
	if (no_moves(game, game->current_player * SECOND_PL_TURN) == 0) {
		game->current_player = game->current_player * (SECOND_PL_TURN);
	}
	if ((game->current_player == FIRST_PL_TURN) && (game->first_player_ai == AI_PLAYING)) {
		return 1;
	}
	if ((game->current_player == SECOND_PL_TURN) && (game->second_player_ai == AI_PLAYING)) {
		return 1;
	}
	return 0;
}

/**
 * Tries all moves on the board for given player,
 * until meeting one that is possible.
 * Erases each move been made.
 */
int no_moves(Game* game, int player) {

	int i = 0, j = 0, k, l;
	int avail_move = -1;
	Move* curr_move = (Move*) malloc(sizeof(Move));
	Board* temp_board = new_board(game->board->n, game->board->m);
	if ((curr_move == NULL) || (temp_board == NULL)) {
		printf("ERROR: Could not check for legal moves\n");
		return 1;
	}
	while ((avail_move == -1) && i < game->board->n) {
		while ((avail_move == -1) && j < game->board->m) {
			curr_move->i = i;
			curr_move->j = j;
			if (game->board->cells[i][j] == 0) {
				for (k = 0; k < game->board->n; k++) {
					// Updating temp board with real state
					for (l = 0; l < game->board->m; l++) {
						temp_board->cells[k][l]= game->board->cells[k][l];
					}
				}
				// Attempt move
				avail_move = game->make_move(temp_board, curr_move, player);
			}
			j++;
		}
		j = 0;
		i++;
	}
	free(curr_move);
	free_board(temp_board);
	return avail_move;
}

// restarts the game from the beginning (the game stays of the same type)
int restart_game(Game *game) {
	free_board(game->board);
	game->board = new_board(game->board->n, game->board->m);
	game->current_player = FIRST_PL_TURN;
	game->init_board(game->board);

	remove_tree(game->tree->root);
	free(game->tree);
	game->tree = create_tree(game->board, game->get_score);
	game->game_over = 0;
	return 1;
}


/**
 * Frees all memory allocated for the game object
 */
void free_game(Game* game) {
	free_board(game->board);
	remove_tree(game->tree->root);
	free(game->tree);
	free(game);
}