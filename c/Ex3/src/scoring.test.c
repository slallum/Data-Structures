/*
 * scoring.test.c
 *
 *  Created on: Dec 21, 2013
 *      Author: shir
 */

#include "scoring.h"

#include <stdio.h>
#include <stdlib.h>

void testConnect4Scoring() {

	int i;
	int **board = calloc(6, sizeof(int*));
	for (i = 0; i < 6; i++) {
		board[i] = calloc(7, sizeof(int));
	}
	board[1][1] = 1;
	board[2][1] = 1;
	board[3][1] = -1;
	board[3][2] = -1;
	board[3][3] = 1;
	board[4][1] = 1;
	board[4][2] = -1;
	board[4][3] = -1;
	board[5][1] = 1;
	board[5][2] = 1;
	board[5][3] = -1;
	board[5][4] = 1;
	board[5][5] = -1;
	board[5][6] = -1;

	printf("%d", connect4_scoring(board, 6, 7));
}

int main() {
	testConnect4Scoring();
	return 0;
}


