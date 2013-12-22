/*
 * game.c
 *
 *  Created on: Dec 17, 2013
 *      Author: shir
 */

#include "game.h"


int make_move(int** cells, int n, int i, int value) {

	int j = 0;
	while ((j < n) && (cells[j][i] == 0)) {
		j++;
	}
	cells[j - 1][i] = value;
	return j;
}
