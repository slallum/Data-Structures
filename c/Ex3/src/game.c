/*
 * game.c
 *
 *  Created on: Dec 17, 2013
 *      Author: shir
 */

#include "game.h"
#include "board.h"
#include "scoring.h"
#include "tree.h"

static int get_first_empty_row(board_t board, int column);


game new_game(int depth) {
    int** cells = {0};
    board_t current_board = { cells, BOARD_HEIGHT, BOARD_WIDTH, &connect4_scoring, &make_move };
    return (game) {.current_board=current_board, .is_comp_turn=0, .tree=NULL, .depth=depth};
}


int make_move(int** cells, int n, int i, int value) {
	int j = 0;
	while ((j < n) && (cells[j][i] == 0)) {
		j++;
	}
	cells[j - 1][i] = value;
	return j;
}


void make_user_move(game *current_game, int move_column) {
    int row_to_insert;
    row_to_insert = get_first_empty_row(current_game->current_board, move_column);
    current_game->current_board.cells[row_to_insert][move_column] = 1;
}

static int get_first_empty_row(board_t board, int column) {
    int i;
    for (i = 1; i<BOARD_HEIGHT; i++) {
        if (board.cells[i][column] == 0) {
            return i-1;
        }
    }
    return -1;
}

int make_comp_move(game *current_game);
int make_connect4_move(int** cells, int n, int i, int value);