#include <stdlib.h>
#include <stdio.h>

#include "connect4_brain.h"

Game *connect4_new_game() {
	int game_difficulties[] = {1,2,3,4,5,6,7};
	Game *game = (Game*)malloc(sizeof(Game));
	if (game == NULL) {
		printf("ERROR: game could not be initialized.");
		return NULL;
	}

	game->board = new_board(BOARD_HEIGHT, BOARD_WIDTH);
	game->is_first_players_turn = 1;

	game->first_player_ai = NO_PLAYER;
	game->second_player_ai = NO_PLAYER;

	game->game_over = 0;

	game->available_moves = available_moves;
	game->won_board = won_board;

	game->depth = 1;
	game->tree = create_tree(game->board, game->depth, make_move, get_score);
	game->difficulties = game_difficulties;

	return game;
}



int** available_moves(Game* game) {

}

int won_board(Game* game) {
	
}

int make_move(int** cells, int n, int m, int value) {
	return 0;
}

int get_score(int** cells, int n, int m) {

}
