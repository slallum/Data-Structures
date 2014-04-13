/*
 * test_reversi_score.c
 *
 *  Created on: Apr 13, 2014
 *      Author: shir
 */


#include "playit_brain.h"
#include "game_framework.h"

int main() {

	int i, correct = 1, score;
	int scores[3] = { 3, -70, 55 };
	int files[3] = { 6, 7, 8};
	Game* game;

	for (i = 0; i < 3; i++) {
		game = load_game(files[i]);
		score = reversi_get_score(game->board);
		correct = correct && (score == scores[i]);
	}

	printf("%d\n", correct);
	return !correct;
}
