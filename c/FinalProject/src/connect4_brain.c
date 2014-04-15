
#include "connect4_brain.h"

/**
 * Creates a new game specific for connect4,
 * with all needed parameters
 */
Game *connect4_new_game() {

	Game *game = (Game*)malloc(sizeof(Game));
	if (game == NULL) {
		printf("ERROR: game could not be initialized.");
		return NULL;
	}
	game->save_game_name = CONNECT4_NAME;
	game->board = new_board(C4_BOARD_N, C4_BOARD_M);
	game->current_player = 1;

	game->first_player_ai = NO_PLAYER;
	game->second_player_ai = NO_PLAYER;
	game->depth_range[0] = 1;
	game->depth_range[1] = 7;
	game->first_player_depth = game->depth_range[0];
	game->second_player_depth = game->depth_range[0];

	game->game_over = 0;

	game->is_valid_move = connect4_is_valid_move;
	game->make_move = connect4_make_move;
	game->won_game = connect4_won_game;
	game->init_board = connect4_init_board;

	game->tree = create_tree(game->board, connect4_get_score);

	game->tiles[0] = C4N_IMG;
	game->tiles[1] = C4P1_IMG;
	game->tiles[3] = C4P2_IMG;
	game->tiles[2] = TROPHY_TILE_IMG;

	return game;
}


/**
 * Nothing special to do
 */
void connect4_init_board(Board* board) {

}

// TODO (ofer) - make_move should use is_valid_move
int connect4_is_valid_move(Board *board, Move *new_move, int value) {
	new_move->i = 0;
	// check when we reach a non empty cell
	while ((new_move->i < board->n) && (board->cells[new_move->i][new_move->j] == 0)) {
		(new_move->i)++;
	}
    // if j IS 0 - it means that the column is full and we'll return -1
	if (new_move->i != 0) {
		return 1;
	}
	if ((new_move->i - 1) == -1) {
		return 0;
	}
	return 1;
}

/*
 * Gets cells, height of cells, column to insert and a value to insert
 * makes the move, according to connect4 laws
 * returns the row of the changed cell
 * if the column is full - returns -1
 * Otherwise, if move was made, returns 0
 */
int connect4_make_move(Board* board, Move* new_move, int value) {
	new_move->i = 0;
	// check when we reach a non empty cell
	while ((new_move->i < board->n) && (board->cells[new_move->i][new_move->j] == 0)) {
		(new_move->i)++;
	}
    // if j IS 0 - it means that the column is full and we'll return -1
    // otherwise - we'll change the value in the cells and return the right row
	if (new_move->i != 0) {
		board->cells[new_move->i - 1][new_move->j] = value;
		return 0;
	}
	return new_move->i - 1;
}

/*
 * Checks if the board has a winning streak (player doesn't matter).
 * Checks spans in each direction.
 * Once finding a winning span, changes their value to winning value.
 */
int connect4_won_game(Game* game) {

	int start[2], end[2], dir[2], strike = 0;
	// Checking forward diagonal
	start[0] = 0;
	start[1] = 0;
	end[0] = game->board->n - 3;
	end[1] = game->board->m - 3;
	dir[0] = 1;
	dir[1] = 1;
	strike = check_spans(game->board, start, end, dir);
	if (!strike) {
		// Checking horizontal spans
		dir[0] = 0;
		end[0] = end[0] + 3;
		strike = check_spans(game->board, start, end, dir);
	}
	if (!strike) {
		// Checking vertical spans
		dir[0] = 1;
		dir[1] = 0;
		end[1] = end[1] + 3;
		end[0] = end[0] - 3;
		strike = check_spans(game->board, start, end, dir);
	}
	if (!strike) {
		// Checking backward diagonal
		start[1] = 3;
		dir[1] = -1;
		strike = check_spans(game->board, start, end, dir);
	}
	if (strike) {
		game->game_over = 1;
	}
	return strike;
}

/**
 * Checks if in any diagonal span on board there is a
 * 4-some, four adjacent, same player discs
 */
int check_spans(Board* board, int start[2], int end[2], int dir[2]) {
	int i = start[0], j = start[1], k, result = 0;
	while ((result < 4) && (result > -4) && (i < end[0])) {
		while ((result < 4) && (result > -4) && (j < end[1])) {
			result = 0;
			// Add 4 adjacent values, according to given direction
			for (k = 0; k < 4; k++) {
				result += board->cells[i + k * dir[0]][j + k * dir[1]];
				// 4 means player 1 winning sequence, -4 means player 2 winning sequence
				if ((result == 4) || (result == -4)) {
					// Set winning value in the 4 winning cells
					for (k = 0; k < 4; k++) {
						board->cells[i + k * dir[0]][j + k * dir[1]] = WINNING_TURN;
					}
				}
			}
			j++;
		}
		j = start[1];
		i++;
	}
	// Indicate was win \ was not win
	return ((result == 4) || (result == -4));
}

/**
 * Scoring function for the connect4 game
 * Each 4 disc span recieves a score and the number
 * of spans for each score are calculated.
 * The outcome vector is multiplied by a weight vector
 */
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
