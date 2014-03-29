#include <stdlib.h>
#include "connect4_brain.h"
#include "game_framework.h"
#include "board.h"
#include "tree.h"

Game *connect4_new_game() {
	// int *game_difficulties = (int*)malloc(sizeof(int)*7);
	int game_difficulties[] = {1,2,3,4,5,6,7};
	Game *game = (Game*)malloc(sizeof(Game));

	game->board = new_board(BOARD_HEIGHT, BOARD_WIDTH);
	game->is_first_players_turn = 1;

	game->first_player_ai = AI_NOT_SET;
	game->second_player_ai = AI_NOT_SET;

	game->game_over = 0;

	// game.new_game = new_game;
	game->available_moves = available_moves;
	game->won_board = won_board;

	game->depth = 1;
	game->tree = create_tree(&(game->board), game->depth);
	game->difficulties = game_difficulties;

	return game;
}

