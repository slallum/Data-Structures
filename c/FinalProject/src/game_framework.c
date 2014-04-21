#include "game_framework.h"

void get_best_move(Game *game, Move *best_move) {
	int depth, max;
	depth = game->current_player == FIRST_PL_TURN ? game->first_player_depth : game->second_player_depth;
	max = game->current_player == FIRST_PL_TURN;
	minmax_with_extend(game->tree->root, depth, -EXTREME_VALUE, EXTREME_VALUE, 
					   max, game->board, best_move,
					   game->is_valid_move, game->make_move, game->get_score);
}

int current_player_is_ai(Game *game) {
	if (game->current_player == FIRST_PL_TURN) {
		return game->first_player_ai;
	} else {
		return game->second_player_ai;
	}
}

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
