/*
 * reversi_brain.c
 *
 *  Created on: Apr 10, 2014
 *      Author: shir
 */


#include "reversi_brain.h"

/**
 * Creates a new game specific for tic-tac-toe,
 * with all needed parameters
 */
Game *reversi_new_game() {
	Game *game = (Game*) malloc(sizeof(Game));
	if (game == NULL) {
		printf("ERROR: game could not be initialized.");
		return NULL;
	}

	game->save_game_name = REVERSI_NAME;
	game->board = new_board(REVERSI_BOARD_N, REVERSI_BOARD_M);
	game->current_player = FIRST_PL_TURN;
	reversi_init_board(game->board);

	game->first_player_ai = NO_PLAYER;
	game->second_player_ai = NO_PLAYER;
	game->depth_range[0] = 1;
	game->depth_range[1] = 4;
	game->first_player_depth = game->depth_range[0];
	game->second_player_depth = game->depth_range[0];

	game->game_over = 0;

	game->is_valid_move = reversi_is_valid_move;
	game->make_move = reversi_make_move;
	game->won_game = reversi_won_game;
	game->init_board = reversi_init_board;

	game->get_score = reversi_get_score;
	game->tree = create_tree(game->board, reversi_get_score);

	game->tiles[0] = RN_IMG;
	game->tiles[1] = RW_IMG;
	game->tiles[3] = RB_IMG;
	game->tiles[2] = TROPHY_TILE_IMG;

	if ((game->board == NULL) || (game->tree == NULL)) {
		return NULL;
	}
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

/**
 * Checks if given move is valid for given player,
 * denoted by value.
 * Doesn't change the board, just checks
 */
int reversi_is_valid_move(Board *board, Move *new_move, int value) {
	int oppAdjacent = 0;
	int i, j;
	int directions[3] = {-1, 0, 1};
	Move* current_dir = (Move*) malloc(sizeof(Move));
	if (current_dir == NULL) {
		printf("Error: Could not validate move\n");
		return 0;
	}
	// Requested cell is taken
	if (board->cells[new_move->i][new_move->j] != 0) {
		return 0;
	}
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			// Check all except no move in no direction
			if ((i != 1) || (j != 1)) {
				current_dir->i = directions[i];
				current_dir->j = directions[j];
				// DON'T CHANGE THE BOARD
				oppAdjacent = consider_move(board, new_move, current_dir, value, 0) || oppAdjacent;
			}
		}
	}
	free(current_dir);
	// Move without adjacent opponent tiles is not legal
	if (!oppAdjacent) {
		return 0;
	}
	return 1;
}


/*
 * Returns 0 if move is legal and was made.
 * Returns -1 Otherwise
 *
 * A legal move is one adjacent to some opponent's tile
 * Also, flips all oppoent's tiles in adjacent streaks
 */
int reversi_make_move(Board* board, Move* new_move, int value) {
	int oppAdjacent = 0;
	int i, j;
	int directions[3] = {-1, 0, 1};
	Move* current_dir = (Move*) malloc(sizeof(Move));
	if (current_dir == NULL) {
		printf("Error: Could not validate move\n");
		return -1;
	}

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
				oppAdjacent = consider_move(board, new_move, current_dir, value, 1) || oppAdjacent;
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
 * @param board			Current board of the game, for checking
 * @param position	    Current position for checking
 * @param direction	    To move for checking validity - can have the values 1, -1, 0
 * 						as it's i / j, to indicate up, down, left, right
 * @param change_board	wheater to change the board's values or not
 */
int consider_move(Board* board, Move* position, Move* direction, int value, int change_board) {

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
				// change the cell in the board only if we asked to
				if (change_board) {
					board->cells[i][j] = value;
				}
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
int reversi_won_game(Game* game) {
	int disk_difference;
	int* avail_moves = count_avail_moves(game->board);
	if (avail_moves != NULL) {
		if ((avail_moves[0] == 0) && (avail_moves[1] == 0)) {
			disk_difference = count_disk_parity(game->board);
			if (disk_difference == 0) {
				game->current_player = 0;
			}
			if (disk_difference > 0) {
				game->current_player = FIRST_PL_TURN;
			} else {
				game->current_player = SECOND_PL_TURN;
			}
			game->game_over = 1;
			free(avail_moves);
			return 1;
		}
		free(avail_moves);
	}
	return 0;
}

/**
 * Checks for each cell on the board, if it is a possible
 * move for player 1 or for player 2 and updates the counts accordingly
 */
int* count_avail_moves(Board* board) {

	int i, j;
	int* moves_count = (int*) malloc(2 * sizeof(int));
	if (moves_count == NULL) {
		return NULL;
	}
	moves_count[0] = 0;
	moves_count[1] = 0;
	Move* curr_move = (Move*) malloc(sizeof(Move));
	Board* temp_board = new_board(board->n, board->m);
	if ((curr_move == NULL) || (temp_board == NULL)) {
		printf("Error: Failed to count available moves\n");
		return moves_count;
	}
	for (i = 0; i < board->n; i++) {
		for (j = 0; j < board->m; j++) {
			reversi_copy_board(board, temp_board);
			curr_move->i = i;
			curr_move->j = j;
			if (reversi_make_move(temp_board, curr_move, FIRST_PL_TURN) == 0) {
				moves_count[0]++;
			}
			reversi_copy_board(board, temp_board);
			if (reversi_make_move(temp_board, curr_move, SECOND_PL_TURN) == 0) {
				moves_count[1]++;
			}
		}
	}
	free(curr_move);
	free(temp_board);
	return moves_count;
}

/**
 * Returns difference between
 * Number of Player 1 and number of Player 2
 * disks on given board
 */
int count_disk_parity(Board* board) {
	int disk_difference = 0;
	int i, j;
	for (i = 0; i < board->n; i++) {
		for (j = 0; j < board->m; j++) {
			disk_difference += board->cells[i][j];
		}
	}
	return disk_difference;
}

/**
 * Heuristic calculation follows:
 * weighted disk parity + 2 * available moves parity + 5 * stability parity
 */
int reversi_get_score(Board* board) {

	int* avail_moves = count_avail_moves(board);
	int moves_parity;
	int disk_parity = weighted_disk_parity(board);
	if (avail_moves == NULL ) {
		moves_parity = 0;
	} else {
		moves_parity = avail_moves[0] - avail_moves[1];
		if ((avail_moves[0] == 0) && (avail_moves[1] == 0)) {
			free(avail_moves);
			if (count_disk_parity(board) > 0) {
				return EXTREME_VALUE;
			} else {
				return -EXTREME_VALUE;
			}
		}
		free(avail_moves);
	}
	return moves_parity * 2 + count_stability_parity(board) * 5 + disk_parity;
}

/**
 * According to simple scoring function (provided for project),
 * counts all values in board, multiplied by the weight
 * corresponding with their position on the board.
 */
int weighted_disk_parity(Board* board) {
	int i;
	int weight[5] = { 1, -1, 5, -5, 10 };
	int (*counter[5])(Board*) = { count_reg_1, count_reg_2, count_reg_3, count_reg_4, count_reg_5 };
	int count = 0;

	for (i = 0; i < 5; i++) {
		count += (counter[i](board) * weight[i]);
	}
	return count;
}

/**
 * Region 1 - the inner square of board
 * (minus 2 rows and 2 coloumns from top, bottom and sides)
 */
int count_reg_1(Board* board) {
	int i, j, count = 0;
	for (i = 2; i < board->n - 2; i++) {
		for (j = 2; j < board->m - 2; j++) {
			count += board->cells[i][j];
		}
	}
	return count;
}

/**
 * Region 2 - second coloumns \ rows from edges,
 * except 2 first and 2 last cells
 *
 */
int count_reg_2(Board* board) {
	int i, count = 0;

	for (i = 2; i < board->m - 2; i++) {
		count += board->cells[1][i];
	}
	for (i = 2; i < board->m - 2; i++) {
		count += board->cells[board->n - 2][i];
	}
	for (i = 2; i < board->n - 2; i++) {
		count += board->cells[i][1];
	}
	for (i = 2; i < board->n - 2; i++) {
		count += board->cells[i][board->m - 2];
	}
	return count;
}

/**
 * Region 3 - first coloumns \ rows from edges,
 * except 2 first and 2 last cells.
 */
int count_reg_3(Board* board) {
	int i, count = 0;

	for (i = 2; i < board->m - 2; i++) {
		count += board->cells[0][i];
	}
	for (i = 2; i < board->m - 2; i++) {
		count += board->cells[board->n - 1][i];
	}
	for (i = 2; i < board->n - 2; i++) {
		count += board->cells[i][0];
	}
	for (i = 2; i < board->n - 2; i++) {
		count += board->cells[i][board->m - 1];
	}
	return count;
}

/**
 * Region 4 - three of each 4 corner cells (except corner cell)
 */
int count_reg_4(Board* board) {
	return board->cells[0][1] + board->cells[1][0] +
			board->cells[1][1] + board->cells[0][board->m - 2] +
			board->cells[1][board->m - 2] + board->cells[1][board->m - 1] +
			board->cells[board->n - 2][0] + board->cells[board->n - 2][1] +
			board->cells[board->n - 1][1] + board->cells[board->n - 2][board->m - 2] +
			board->cells[board->n - 1][board->m - 2] + board->cells[board->n - 2][board->m - 1];
}

/**
 * Region 5 - corners
 */
int count_reg_5(Board* board) {
	return board->cells[0][0] +
			board->cells[0][board->m - 1] +
			board->cells[board->n - 1][0] +
			board->cells[board->n - 1][board->m - 1];
}

/**
 * Counts the difference in the stability between first and second players,
 * where stability is the number of stable pieces.
 * A stable piece is one that can never be flipped again in the game.
 * This happens if piece is in the corner,
 * on edge with only same coloured pieces between it and a neighbour corner,
 * or in any position within a diagonal between two stable pieces.
 */
int count_stability_parity(Board* board) {

	int stability_parity = 0;

	stability_parity += count_stability_section(board, 0, 0, board->n, board->m, 1, 1);
	stability_parity += count_stability_section(board, 0, board->m - 1, board->n, 0, 1, -1);
	stability_parity += count_stability_section(board, board->n - 1, board->m - 1, 0, 0, -1, -1);
	stability_parity += count_stability_section(board, board->n - 1, 0, 0, board->m, -1, 1);

	return stability_parity;
}

/**
 * Checks if tiles are stable from the forner (i_start, j_start)
 * towards the corner (i_end, j_end) according to (i_dir, j_dir)
 */
int count_stability_section(Board* board, int i_start, int j_start,
		int i_end, int j_end, int i_dir, int j_dir) {

	int i = i_start, j = j_start + j_dir;
	int stability_parity = board->cells[i][j - j_dir];
	while ((i != i_end) && (j != j_start) && (board->cells[i][j] != 0)) {
		while ((j != j_end)	&& (board->cells[i][j] == board->cells[i][j - j_dir])) {
			stability_parity += board->cells[i][j];
			j += j_dir;
		}
		j_end = j;
		j = j_start;
		i += i_dir;
		if ((i != i_end) && (board->cells[i][j] == board->cells[i - i_dir][j])) {
			stability_parity += board->cells[i][j];
			j += j_dir;
		}
	}
	return stability_parity;
}

/**
 * Copy each value of each cell in from_board
 * to the corresponding cell in to_board
 */
void reversi_copy_board(Board* from_board, Board* to_board) {
	int i, j;
	for (i = 0; i < from_board->n; i++) {
		for (j = 0; j < to_board->m; j++) {
			to_board->cells[i][j] = from_board->cells[i][j];
		}
	}
}

