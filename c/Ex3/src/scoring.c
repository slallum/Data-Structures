/*
 * scoring.c
 *
 *  Created on: Dec 21, 2013
 *      Author: shir
 */

#include "scoring.h"

static void count_horizontal(int *spans_count, int** board, int n, int m);
static void count_vertical(int *spans_count, int** board, int n, int m);
static void count_diagonal(int *spans_count, int** board, int n, int m);

/**
 * Scoring function for the connect4 game
 * Each 4 disc span recieves a score and the number
 * of spans for each score are calculated.
 * The outcome vector is multiplied by a weight vector
 */
int connect4_scoring(int** board, int n, int m) {

	int weight[9] = { 0, -5, -2, -1, 0, 1, 2, 5, 0};
	int spans_count[9] = { 0 };
	int i;
	int result = 0;

	count_horizontal((int*)&spans_count, board, n, m);
	count_vertical((int*)&spans_count, board, n, m);
	count_diagonal((int*)&spans_count, board, n, m);

	// Negative player wins
	if (spans_count[0] > 0) {
		return -1000000;
	}
	// Positive player wins
	if (spans_count[8] > 0) {
		return 1000000;
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
static void count_horizontal(int *spans_count, int** board, int n, int m) {
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
static void count_vertical(int *spans_count, int** board, int n, int m) {

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
static void count_diagonal(int *spans_count, int** board, int n, int m) {

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
