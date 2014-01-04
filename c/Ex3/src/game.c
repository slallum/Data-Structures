/*
 * game.c
 *
 *  Created on: Dec 17, 2013
 *      Author: shir
 */

#include <stdlib.h>

#include "game.h"
#include "board.h"
#include "scoring.h"
#include "tree.h"

static int get_first_empty_row(board_t board, int column);


game *new_game(int depth) {
    int **cells;
    int i, j;
    game* result = (game*)malloc(sizeof(game));

    // allocate all the cells
    if ((cells = (int**)malloc(BOARD_HEIGHT * sizeof(int*))) == NULL) {
        perror("Error: standard function malloc has failed");
        return NULL;
    }
    for (i=0; i<BOARD_HEIGHT; i++) {
        if ((cells[i] = (int*)malloc(BOARD_WIDTH * sizeof(int))) == NULL) {
            perror("Error: standard function malloc has failed");
            return NULL;
        }
    }
    // init cells with zeros
    for (i=0; i<BOARD_HEIGHT; i++) {
        for (j=0; j<BOARD_WIDTH; j++) {
            cells[i][j] = 0;
        }
    }
    // create  the board
    board_t current_board = { cells, BOARD_HEIGHT, BOARD_WIDTH, &connect4_scoring, &make_connect4_move };

    result->current_board = current_board;
    result->is_comp_turn = 0;
    result->tree=NULL;
    result->depth=depth;
    result->game_over=0;
    return result;
}


int make_connect4_move(int** cells, int n, int i, int value) {
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


/*
 * checks if the board has a winning streak (the player who won doesn't matter)
 */
int won_board(board_t board) {
    int score = connect4_scoring(board.cells, BOARD_HEIGHT, BOARD_WIDTH);
    if (score == EXTREME_VALUE || score == -EXTREME_VALUE) {
        return 1;
    } else {
        return 0;
    }
}

/*
 * returns pointer to the column that the computer will add disc to
 * returns NULL if there was an error while executing some allocationg command
 */
int *get_computer_move(game *current_game) {
    // TODO: implement
    return 0;
}

/*
 * gets the best column to insert a disc if the current player is the user
 */
int* get_best_move_for_player(game *current_game) {
    // TODO: implement
    return 0;
}

vertex *run_minmax_on_vertex(vertex *v, int is_comp_turn) {
    // is leaf?
    int min = EXTREME_VALUE;
    int max = -EXTREME_VALUE;
    element *iterator;
    vertex *chosen_vertex;

    // stop the iteration if this vertex is a leaf or if the vertex's score indicates that somebody already won
    if ((v->children == NULL) || v->score == EXTREME_VALUE || v->score == -EXTREME_VALUE) {
        return v;
    }
    // recursion with min
    iterator = v->children->head;
    if (is_comp_turn) {
        do {
            if (iterator->node->score < min) {
                min = iterator->node->score;
                chosen_vertex = iterator->node;
            }
            iterator = iterator->next;
        }
        while (iterator->next != NULL);
    } else {
        do {
            if (iterator->node->score < max) {
                max = iterator->node->score;
                chosen_vertex = iterator->node;
            }
            iterator = iterator->next;
        }
        while (iterator->next != NULL);
    }
    v->score = chosen_vertex->score;
    return chosen_vertex;
}