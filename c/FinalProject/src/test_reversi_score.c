/*
 * test_reversi_score.c
 *
 *  Created on: Apr 13, 2014
 *      Author: shir
 */


#include "playit_brain.h"
#include "game_framework.h"
#include "contest.c"

int main() {

	int i, correct = 1, score, j, k;
	int scores[3] = { 3, -70, 55 };
	int files[3] = { 6, 7, 8};
	Game* game;
	int ichs_board[64];

	for (i = 0; i < 3; i++) {
		game = load_game(files[i]);
		for (j = 0; j < OS_BOARD_SIZE; j++) {
			for (k = 0; k < OS_BOARD_SIZE; k++) {
				ichs_board[j * OS_BOARD_SIZE + k] = game->board->cells[j][k];
			}
		}
		score = calc_score_reversi(ichs_board);
//		score = reversi_get_score(game->board);
		correct = correct && (score == scores[i]);
	}

	printf("%d\n", correct);
	return !correct;
}
