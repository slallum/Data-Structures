/*
 * contest.c
 *
 *  Created on: Apr 21, 2014
 *      Author: shir
 */

#include <stdlib.h>
#include <stdio.h>
#define OS_EXTREME_VALUE 100000
#define OS_FIRST_PL_TURN	1
#define OS_SECOND_PL_TURN	-1
#define OS_BOARD_SIZE		8

/**
 * Returns difference between
 * Number of Player 1 and number of Player 2
 * disks on given board
 */
int OS_count_disk_parity(int* board) {
	int disk_difference = 0;
	int i, j;
	for (i = 0; i < OS_BOARD_SIZE; i++) {
		for (j = 0; j < OS_BOARD_SIZE; j++) {
			disk_difference += board[i * OS_BOARD_SIZE + j];
		}
	}
	return disk_difference;
}

/**
 *
 * @param board			Current board of the game, for checking
 * @param position	    Current position for checking
 * @param direction	    To move for checking validity - can have the values 1, -1, 0
 * 						as it's i / j, to indicate up, down, left, right
 * @param change_board	wheater to change the board's values or not
 */
int OS_consider_move(int* board, int* position, int* direction, int value, int change_board) {

	int i = position[0] + direction[0];
	int j = position[1] + direction[1];

	if ((i < 0) || (j < 0) || (i >= OS_BOARD_SIZE) || (j >= OS_BOARD_SIZE)) {
		return 0;
	}
	if (board[i * OS_BOARD_SIZE + j] == value * OS_SECOND_PL_TURN) {
		// Explore through board according to requested direction
		while ((i + direction[0] >= 0) && (i + direction[0] < OS_BOARD_SIZE) &&
				(j + direction[1] >= 0) && ( j + direction[1] < OS_BOARD_SIZE) &&
				(board[i * OS_BOARD_SIZE + j] == value * OS_SECOND_PL_TURN)) {
			i += direction[0];
			j += direction[1];
		}
		// Move is valid if reached tile of original value
		if (board[i * OS_BOARD_SIZE + j] == value) {
			// Go back and flip all tiles
			while ((i != position[0]) || (j != position[1])) {
				i -= direction[0];
				j -= direction[1];
				// change the cell in the board only if we asked to
				if (change_board) {
					board[i * OS_BOARD_SIZE + j] = value;
				}
			}
			return 1;
		}
	}
	return 0;
}

int OS_is_valid_move(int* board, int* new_move, int value) {
	int oppAdjacent = 0;
	int i, j;
	int directions[3] = {-1, 0, 1};
	int current_dir[2];

	// Requested cell is taken
	if (board[new_move[0] * OS_BOARD_SIZE + new_move[1]] != 0) {
		return 0;
	}
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			// Check all except no move in no direction
			if ((i != 1) || (j != 1)) {
				current_dir[0] = directions[i];
				current_dir[1] = directions[j];
				// DON'T CHANGE THE BOARD
				oppAdjacent = OS_consider_move(board, new_move, current_dir, value, 0) || oppAdjacent;
			}
		}
	}
	// Move without adjacent opponent tiles is not legal
	if (!oppAdjacent) {
		return 0;
	}
	return 1;
}

/**
 * Checks for each cell on the board, if it is a possible
 * move for player 1 or for player 2 and updates the counts accordingly
 */
int* OS_count_avail_moves(int* board) {

	int i, j, curr_move[2];
	int* moves_count = (int*) malloc(2 * sizeof(int));
	if (moves_count == NULL) {
		return NULL;
	}
	moves_count[0] = 0;
	moves_count[1] = 0;

	for (i = 0; i < OS_BOARD_SIZE; i++) {
		for (j = 0; j < OS_BOARD_SIZE; j++) {
			curr_move[0] = i;
			curr_move[1] = j;
			if (OS_is_valid_move(board, curr_move, OS_FIRST_PL_TURN) == 1) {
				moves_count[0]++;
			}
			if (OS_is_valid_move(board, curr_move, OS_SECOND_PL_TURN) == 1) {
				moves_count[1]++;
			}
		}
	}
	return moves_count;
}

/**
 * Region 1 - the inner square of board
 * (minus 2 rows and 2 coloumns from top, bottom and sides)
 */
int OS_count_reg_1(int* board) {
	int i, j, count = 0;
	for (i = 2; i < OS_BOARD_SIZE - 2; i++) {
		for (j = 2; j < OS_BOARD_SIZE - 2; j++) {
			count += board[i * OS_BOARD_SIZE + j];
		}
	}
	return count;
}

/**
 * Region 2 - second coloumns \ rows from edges,
 * except 2 first and 2 last cells
 *
 */
int OS_count_reg_2(int* board) {
	int i, count = 0;

	for (i = 2; i < OS_BOARD_SIZE - 2; i++) {
		count += board[1 * OS_BOARD_SIZE + i];
	}
	for (i = 2; i < OS_BOARD_SIZE - 2; i++) {
		count += board[(OS_BOARD_SIZE - 2) * OS_BOARD_SIZE + i];
	}
	for (i = 2; i < OS_BOARD_SIZE - 2; i++) {
		count += board[i * OS_BOARD_SIZE + 1];
	}
	for (i = 2; i < OS_BOARD_SIZE - 2; i++) {
		count += board[i * OS_BOARD_SIZE + (OS_BOARD_SIZE - 2)];
	}
	return count;
}

/**
 * Region 3 - first coloumns \ rows from edges,
 * except 2 first and 2 last cells.
 */
int OS_count_reg_3(int* board) {
	int i, count = 0;

	for (i = 2; i < OS_BOARD_SIZE - 2; i++) {
		count += board[i];
	}
	for (i = 2; i < OS_BOARD_SIZE - 2; i++) {
		count += board[(OS_BOARD_SIZE - 1) * OS_BOARD_SIZE + i];
	}
	for (i = 2; i < OS_BOARD_SIZE - 2; i++) {
		count += board[i * OS_BOARD_SIZE];
	}
	for (i = 2; i < OS_BOARD_SIZE - 2; i++) {
		count += board[i * OS_BOARD_SIZE + (OS_BOARD_SIZE - 1)];
	}
	return count;
}

/**
 * Region 4 - three of each 4 corner cells (except corner cell)
 */
int OS_count_reg_4(int* board) {
	return board[1] + board[OS_BOARD_SIZE] +
			board[OS_BOARD_SIZE + 1] + board[OS_BOARD_SIZE - 2] +
			board[OS_BOARD_SIZE + OS_BOARD_SIZE - 2] + board[OS_BOARD_SIZE + OS_BOARD_SIZE - 1] +
			board[(OS_BOARD_SIZE - 2) * OS_BOARD_SIZE] + board[(OS_BOARD_SIZE - 2) * OS_BOARD_SIZE + 1] +
			board[(OS_BOARD_SIZE - 1) * OS_BOARD_SIZE + 1] + board[(OS_BOARD_SIZE - 2) * OS_BOARD_SIZE + (OS_BOARD_SIZE - 2)] +
			board[(OS_BOARD_SIZE - 1) * OS_BOARD_SIZE + (OS_BOARD_SIZE - 2)] + board[(OS_BOARD_SIZE - 2) * OS_BOARD_SIZE + (OS_BOARD_SIZE - 1)];
}

/**
 * Region 5 - corners
 */
int OS_count_reg_5(int* board) {
	return board[0] +
			board[OS_BOARD_SIZE - 1] +
			board[(OS_BOARD_SIZE - 1) * OS_BOARD_SIZE] +
			board[(OS_BOARD_SIZE - 1) * OS_BOARD_SIZE + OS_BOARD_SIZE - 1];
}

/**
 * According to simple scoring function (provided for project),
 * counts all values in board, multiplied by the weight
 * corresponding with their position on the board.
 */
int OS_weighted_disk_parity(int* board) {
	int i;
	int weight[5] = { 1, -1, 5, -5, 10 };
	int (*counter[5])(int*) = { OS_count_reg_1, OS_count_reg_2, OS_count_reg_3, OS_count_reg_4, OS_count_reg_5 };
	int count = 0;

	for (i = 0; i < 5; i++) {
		count += (counter[i](board) * weight[i]);
	}
	return count;
}

/**
 * Checks if tiles are stable from the forner (i_start, j_start)
 * towards the corner (i_end, j_end) according to (i_dir, j_dir)
 */
int OS_count_stability_section(int* board, int i_start, int j_start,
		int i_end, int j_end, int i_dir, int j_dir) {

	int i = i_start, j = j_start + j_dir;
	int stability_parity = board[i * OS_BOARD_SIZE + j - j_dir];
	while ((i != i_end) && (j != j_start) && (board[i * OS_BOARD_SIZE + j] != 0)) {
		while ((j != j_end)	&& (board[i * OS_BOARD_SIZE + j] == board[i * OS_BOARD_SIZE + j - j_dir])) {
			stability_parity += board[i * OS_BOARD_SIZE + j];
			j += j_dir;
		}
		j_end = j;
		j = j_start;
		i += i_dir;
		if ((i != i_end) && (board[i * OS_BOARD_SIZE + j] == board[(i - i_dir) * OS_BOARD_SIZE + j])) {
			stability_parity += board[i * OS_BOARD_SIZE + j];
			j += j_dir;
		}
	}
	return stability_parity;
}


/**
 * Counts the difference in the stability between first and second players,
 * where stability is the number of stable pieces.
 * A stable piece is one that can never be flipped again in the game.
 * This happens if piece is in the corner,
 * on edge with only same coloured pieces between it and a neighbour corner,
 * or in any position within a diagonal between two stable pieces.
 */
int OS_count_stability_parity(int* board) {

	int stability_parity = 0;

	stability_parity += OS_count_stability_section(board, 0, 0, OS_BOARD_SIZE, OS_BOARD_SIZE, 1, 1);
	stability_parity += OS_count_stability_section(board, 0, OS_BOARD_SIZE - 1, OS_BOARD_SIZE, 0, 1, -1);
	stability_parity += OS_count_stability_section(board, OS_BOARD_SIZE - 1, OS_BOARD_SIZE - 1, 0, 0, -1, -1);
	stability_parity += OS_count_stability_section(board, OS_BOARD_SIZE - 1, 0, 0, OS_BOARD_SIZE, -1, 1);

	return stability_parity;
}




int calc_score_reversi(int* board) {

	int* avail_moves = OS_count_avail_moves(board);
	int moves_parity;
	int disk_parity = OS_weighted_disk_parity(board);
	if (avail_moves == NULL ) {
		moves_parity = 0;
	} else {
		moves_parity = avail_moves[0] - avail_moves[1];
		if ((avail_moves[0] == 0) && (avail_moves[1] == 0)) {
			free(avail_moves);
			if (OS_count_disk_parity(board) > 0) {
				return OS_EXTREME_VALUE;
			} else {
				return -OS_EXTREME_VALUE;
			}
		}
		free(avail_moves);
	}
	return moves_parity * 2 + OS_count_stability_parity(board) * 5 + disk_parity;
}



