/*
 * scoring.test.c
 *
 *  Created on: Dec 21, 2013
 *      Author: shir
 */

#include "scoring.h"
#include "board.h"

#include <stdio.h>
#include <stdlib.h>

void testConnect4Scoring() {

	board_t board;
	int i;
	int **cells = calloc(6, sizeof(int*));
	for (i = 0; i < 6; i++) {
		cells[i] = calloc(7, sizeof(int));
	}
	cells[1][1] = 1;
	cells[2][1] = 1;
	cells[3][1] = -1;
	cells[3][2] = -1;
	cells[3][3] = 1;
	cells[4][1] = 1;
	cells[4][2] = -1;
	cells[4][3] = -1;
	cells[5][1] = 1;
	cells[5][2] = 1;
	cells[5][3] = -1;
	cells[5][4] = 1;
	cells[5][5] = -1;
	cells[5][6] = -1;
	board = (board_t){.cells = cells,.n = 6, .m = 7, .scoring_func=*connect4_scoring, .make_move=NULL};
	print_board(&board);
	printf("%d", get_score(&board));
}

int main() {
	testConnect4Scoring();
	return 0;
}


