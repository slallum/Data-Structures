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