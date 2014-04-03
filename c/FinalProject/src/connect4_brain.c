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

	game->board = new_board(C4_BOARD_N, C4_BOARD_M);
	game->is_first_players_turn = 1;

	game->first_player_ai = NO_PLAYER;
	game->second_player_ai = NO_PLAYER;

	game->game_over = 0;

	game->make_move = connect4_make_move;
	game->available_moves = connect4_available_moves;
	game->won_board = connect4_won_board;

	game->depth = 1;
//	game->tree = create_tree(game->board, game->depth, connect4_make_move, connect4_get_score);
	game->difficulties = game_difficulties;

	game->tiles[0] = C4N_IMG;
	game->tiles[1] = C4P1_IMG;
	game->tiles[2] = C4P2_IMG;

	return game;
}

int** connect4_available_moves(Game* game) {
	return NULL;
}

int connect4_make_move(Board* board, int i, int j, int value) {

	// check when we reach a non empty cell
	while ((i < board->n) && (board->cells[i][j] == 0)) {
		i++;
	}
    // if j IS 0 - it means that the column is full and we'll return -1
    // otherwise - we'll change the value in the cells and return the right row
	if (i != 0) {
		board->cells[i - 1][j] = value;
	}
	return i - 1;
}

int connect4_won_board(Board* board) {
    int score = connect4_get_score(board);
    if (score == EXTREME_VALUE || score == -EXTREME_VALUE) {
        return 1;
    } else {
        return 0;
    }
}

int connect4_get_score(Board* board) {
	int weight[9] = { 0, -5, -2, -1, 0, 1, 2, 5, 0 };
	int spans_count[9] = { 0 };
	int i;
	int result = 0;

	count_horizontal(spans_count, board->cells, board->n, board->m);
	count_vertical(spans_count, board->cells, board->n, board->m);
	count_diagonal(spans_count, board->cells, board->n, board->m);

	// Negative player wins
	if (spans_count[0] > 0) {
		return -EXTREME_VALUE;
	}
	// Positive player wins
	if (spans_count[8] > 0) {
		return EXTREME_VALUE;
	}
	// Multiply sums with the weight function
	for (i = 0; i < 9; i++) {
		result += weight[i] * spans_count[i];
	}
	return result;
}

/**
 * Goes over all horizontal spans on board.
 * For each row, calcs first span and then just updates each step
 */
void count_horizontal(int *spans_count, int** board, int n, int m) {
	int i, j;
	int result = 0;

	// Rows
	for (i = 0; i < n; i++) {
		result = board[i][0] + board[i][1] + board[i][2] + board[i][3];
		spans_count[result + 4] += 1;
		// Coloumns
		for (j = 4; j < m; j++) {
			result -= board[i][j - 4];
			result += board[i][j];
			spans_count[result + 4] += 1;
		}
	}
}

/**
 * Goes over all vertical spans on board.
 * For each coloumn, calcs first span and then just update each step.
 */
void count_vertical(int *spans_count, int** board, int n, int m) {

	int i, j;
	int result = 0;
	// Coloums
	for (i = 0; i < m; i++) {
		result = board[0][i] + board[1][i] + board[2][i] + board[3][i];
		spans_count[result + 4] += 1;
		// Rows
		for (j = 4; j < n; j++) {
			result -= board[j - 4][i];
			result += board[j][i];
			spans_count[result + 4] += 1;
		}
	}
}

/**
 * Goes over all diagonal spans on board.
 * First goes over 'forward' diagonals, then 'backward' ones.
 */
void count_diagonal(int *spans_count, int** board, int n, int m) {

	int i, j;
	int result = 0;
	// Count all forward diagonals
	for (i = 0; i < n - 3; i++) {
		for (j = 0; j < m - 3; j++) {
			// Taking elements forward
			result = board[i][j] + board[i+1][j+1] + board[i+2][j+2] + board[i+3][j+3];
			spans_count[result + 4] += 1;
		}
	}
	// Count all backward diagonals
	result = 0;
	for (i = 0; i < n - 3; i++) {
		for (j = 3; j < m; j++) {
			// Taking elements backward
			result = board[i][j] + board[i+1][j-1] + board[i+2][j-2] + board[i+3][j-3];
			spans_count[result + 4] += 1;
		}
	}
}
