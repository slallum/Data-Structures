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
	game->is_first_players_turn = 1;

	game->first_player_ai = NO_PLAYER;
	game->second_player_ai = NO_PLAYER;
	game->depth_range[0] = 9;
	game->depth_range[1] = 9;
	game->first_player_depth = game->depth_range[0];
	game->second_player_depth = game->depth_range[0];

	game->game_over = 0;

	game->make_move = ttt_make_move;
	game->won_game = ttt_won_game;
	game->init_board = ttt_init_board;

//	game->tree = create_tree(game->board, game->depth, ttt_make_move, ttt_get_score);

	game->tiles[0] = TTTN_IMG;
	game->tiles[1] = TTTX_IMG;
	game->tiles[2] = TTTO_IMG;

	return game;
}

/**
 * No need for special preparation
 */
void ttt_init_board(Board* board) {

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
Move** ttt_won_game(Game* game) {

	Move** winning_span = ttt_won_board(game->board);
	if (winning_span != NULL) {
		game->game_over = 1;
	}
	return winning_span;
}

Move** ttt_won_board(Board* board) {
	int i = 0, j = 0;
	Move** winning_span = NULL;
	int players[2] = { FIRST_PL_TURN, SECOND_PL_TURN };

	while ((winning_span == NULL) && (i < TTT_BOARD_N)) {
		while ((winning_span == NULL) && (j < 2)) {
			winning_span = checkHorizontal(i, board, players[j]);
			if (winning_span == NULL) {
				winning_span = checkVertical(i, board, players[j]);
			}
			j++;
		}
		j = 0;
		i++;
	}
	while ((winning_span == NULL) && (j < 2)) {
		winning_span = checkMainDiag(board, players[j]);
		if (winning_span == NULL) {
			winning_span = checkSecDiag(board, players[j]);
		}
		j++;
	}
	return winning_span;
}


Move** checkHorizontal(int i, Board* board, int value) {
	int j = 0, strike = 1, k;
	Move** winning_span = (Move**) malloc(sizeof(Move*) * 4);
	// Checking horizontal strike
	while ((strike == 1) && (j < TTT_BOARD_M)) {
		strike = strike && (board->cells[i][j] == value);
		j++;
	}
	if (strike) {
		for (k = 0; k < 3; k++) {
			winning_span[k] = (Move*) malloc(sizeof(Move));
			winning_span[k]->i = i;
			winning_span[k]->j = k;
		}
		winning_span[3] = NULL;
		return winning_span;
	} else {
		return NULL;
	}
}

Move** checkVertical(int i, Board* board, int value) {
	int j = 0, strike = 1, k;
	Move** winning_span = (Move**) malloc(sizeof(Move*) * 4);
	while ((strike == 1) && (j < TTT_BOARD_M)) {
		strike = strike && (board->cells[j][i] == value);
		j++;
	}
	if (strike) {
		for (k = 0; k < 3; k++) {
			winning_span[k] = (Move*) malloc(sizeof(Move));
			winning_span[k]->i = k;
			winning_span[k]->j = i;
		}
		winning_span[3] = NULL;
		return winning_span;
	} else {
		return NULL;
	}
}

Move** checkMainDiag(Board* board, int value) {
	int i = 0, strike = 1, k;
	Move** winning_span = (Move**) malloc(sizeof(Move*) * 4);
	while ((strike == 1) && (i < TTT_BOARD_M)) {
		strike = strike && (board->cells[i][i] == value);
		i++;
	}
	if (strike) {
		for (k = 0; k < 3; k++) {
			winning_span[k] = (Move*) malloc(sizeof(Move));
			winning_span[k]->i = k;
			winning_span[k]->j = k;
		}
		winning_span[3] = NULL;
		return winning_span;
	} else {
		return NULL;
	}
}

Move** checkSecDiag(Board* board, int value) {
	int i = TTT_BOARD_M - 1, j = 0, k;
	Move** winning_span = (Move**) malloc(sizeof(Move*) * 4);
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
			winning_span[k] = (Move*) malloc(sizeof(Move));
			winning_span[k]->i = k;
			winning_span[k]->j = TTT_BOARD_M - k;
		}
		winning_span[3] = NULL;
		return winning_span;
	} else {
		return NULL;
	}
}

/**
 * Tic Tac Toe AI is so clever, it can see until
 * last move of the game.
 * Therefore, need to indicate only winning board
 */
int ttt_get_score(Board* board) {
	if (ttt_won_board(board)) {
		return 1;
	} else {
		return 0;
	}
}

