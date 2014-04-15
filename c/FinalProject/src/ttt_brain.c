/*
 * ttt_brain.c
 *
 *  Created on: Apr 10, 2014
 *      Author: shir
 */

#include "ttt_brain.h"

Game *ttt_new_game() {
	Game *game = (Game*)malloc(sizeof(Game));
	if (game == NULL) {
		printf("ERROR: game could not be initialized.");
		return NULL;
	}
	game->save_game_name = TTT_NAME;
	game->board = new_board(TTT_BOARD_N, TTT_BOARD_M);
	game->current_player = 1;

	game->first_player_ai = NO_PLAYER;
	game->second_player_ai = NO_PLAYER;
	game->depth_range[0] = 9;
	game->depth_range[1] = 9;
	game->first_player_depth = game->depth_range[0];
	game->second_player_depth = game->depth_range[0];

	game->game_over = 0;

	game->is_valid_move = ttt_is_valid_move;
	game->make_move = ttt_make_move;
	game->won_game = ttt_won_game;
	game->init_board = ttt_init_board;

	game->tree = create_tree(game->board, ttt_get_score);

	game->tiles[0] = TTTN_IMG;
	game->tiles[1] = TTTX_IMG;
	game->tiles[3] = TTTO_IMG;
	game->tiles[2] = TROPHY_TILE_IMG;

	return game;
}

/**
 * No need for special preparation
 */
void ttt_init_board(Board* board) {

}

int ttt_is_valid_move(Board *board, Move *move, int value) {
	if (board->cells[new_move->i][new_move->j] != 0) {
		return 0;
	}
	return 1;
}

/*
 *
 * @param board		Current board of the game
 * @param new_move	Indexes in board requested as next move (by some player)
 * @param value		Value for the played move, indicating the player
 *
 * @return	-1 if cell is already taken by some player
 * 			 0 if move was made
 */
int ttt_make_move(Board* board, Move* new_move, int value) {

	if (board->cells[new_move->i][new_move->j] != 0) {
		return -1;
	}
	board->cells[new_move->i][new_move->j] = value;
	return 0;
}


/*
 * If there are 3 of same symbol in a row - player won
 */
int ttt_won_game(Game* game) {

	if (ttt_won_board(game->board)) {
		game->game_over = 1;
		return 1;
	}
	return 0;
}

int ttt_won_board(Board* board) {
	int i = 0, j = 0, strike = 0;
	int players[2] = { FIRST_PL_TURN, SECOND_PL_TURN };

	while (!strike && (i < TTT_BOARD_N)) {
		while (!strike && (j < 2)) {
			strike = check_horizontal(i, board, players[j]);
			if (!strike) {
				strike = check_vertical(i, board, players[j]);
			}
			j++;
		}
		j = 0;
		i++;
	}
	while (!strike && (j < 2)) {
		strike = check_main_diag(board, players[j]);
		if (!strike) {
			strike = check_sec_diag(board, players[j]);
		}
		j++;
	}
	if (strike) {
		return players[j - 1];
	}
	return 0;
}


int check_horizontal(int i, Board* board, int value) {
	int j = 0, strike = 1, k;
	while ((strike == 1) && (j < TTT_BOARD_M)) {
		strike = strike && (board->cells[i][j] == value);
		j++;
	}
	if (strike) {
		for (k = 0; k < 3; k++) {
			board->cells[i][k] = 2;
		}
		return 1;
	} else {
		return 0;
	}
}

int check_vertical(int i, Board* board, int value) {
	int j = 0, strike = 1, k;
	while ((strike == 1) && (j < TTT_BOARD_M)) {
		strike = strike && (board->cells[j][i] == value);
		j++;
	}
	if (strike) {
		for (k = 0; k < 3; k++) {
			board->cells[k][i] = 2;
		}
		return 1;
	} else {
		return 0;
	}
}

int check_main_diag(Board* board, int value) {
	int i = 0, strike = 1, k;
	while ((strike == 1) && (i < TTT_BOARD_M)) {
		strike = strike && (board->cells[i][i] == value);
		i++;
	}
	if (strike) {
		for (k = 0; k < 3; k++) {
			board->cells[k][k] = 2;
		}
		return 1;
	} else {
		return 0;
	}
}

int check_sec_diag(Board* board, int value) {
	int i = TTT_BOARD_M - 1, j = 0, k;
	int strike = 1;
	while ((strike == 1) && (i >= 0)) {
		while ((strike == 1) && (j < TTT_BOARD_M)) {
			strike = strike && (board->cells[i][j] == value);
			i--;
			j++;
		}
	}
	if (strike) {
		for (k = 0; k < 3; k++) {
			board->cells[k][TTT_BOARD_M - 1 - k] = 2;
		}
		return 1;
	} else {
		return 0;
	}
}

/**
 * Tic Tac Toe AI is so clever, it can see until
 * last move of the game.
 * Therefore, need to indicate only winning board
 */
int ttt_get_score(Board* board) {

	int who_won = ttt_won_board(board) == FIRST_PL_TURN;
	if (who_won == FIRST_PL_TURN) {
		return EXTREME_VALUE;
	}
	if (who_won == SECOND_PL_TURN) {
		return -EXTREME_VALUE;
	}
	return 0;
}

