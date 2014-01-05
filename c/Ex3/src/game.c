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


int new_game(game *current_game, int depth) {
    int **cells;
    int i, j;
    // allocate all the cells
    if ((cells = (int**)malloc(BOARD_HEIGHT * sizeof(int*))) == NULL) {
        perror("Error: standard function malloc has failed");
        return 0;
    }
    for (i=0; i<BOARD_HEIGHT; i++) {
        if ((cells[i] = (int*)malloc(BOARD_WIDTH * sizeof(int*))) == NULL) {
            perror("Error: standard function malloc has failed");
            return 0;
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

    current_game->current_board = current_board;
    current_game->is_comp_turn = 0;
    if (depth == -1) {
    	if ((current_game->tree = create_tree(&(current_game->current_board), 1)) == NULL) {
			return 0;
		}
    } else {
    	if ((current_game->tree = create_tree(&(current_game->current_board), depth)) == NULL) {
			return 0;
		}
    }
    current_game->depth=depth;
    current_game->game_over=0;
    return 1;
}


int make_connect4_move(int** cells, int n, int i, int value) {
	int j = 0;
	while ((j < n) && (cells[j][i] == 0)) {
		j++;
	}
	if (j != 0) {
		cells[j - 1][i] = value;
	}
	return j - 1;
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
int get_computer_move(game *current_game) {
//    vertex *next_vertex;
//    next_vertex = run_minmax_on_vertex(current_game->tree->root, 1);
//    return &(next_vertex->column_num);
    return get_best_coloumn(current_game->tree->root, current_game->depth, 1);
}

/*
 * gets the best column to insert a disc if the current player is the user
 */
int get_best_move_for_player(game *current_game) {
//    vertex *next_vertex;
//    next_vertex = run_minmax_on_vertex(current_game->tree->root, 0);
//    return &(next_vertex->column_num);
	return get_best_coloumn(current_game->tree->root, current_game->depth, 1);
}

int get_best_coloumn(vertex* current_node, int depth, int max) {

	element* iterator;
	int decsendent_score, best_coloumn;
	int extreme_score = (max ? -EXTREME_VALUE : EXTREME_VALUE);
	if ((current_node->children == NULL) || (depth == 0)
			|| (current_node->score == EXTREME_VALUE)
			|| (current_node->score == -EXTREME_VALUE)) {
		return -1;
	}
	iterator = current_node->children->head;
	while (iterator != NULL) {
		decsendent_score = calculate_minmax(iterator->node, depth - 1, !max);
		if ((max && decsendent_score > extreme_score)
				|| (!max && decsendent_score < extreme_score)) {
			extreme_score = decsendent_score;
			best_coloumn = iterator->node->column_num;
		}
		iterator = iterator->next;
	}
	return best_coloumn;
}

int calculate_minmax(vertex* current_node, int depth, int max) {

	element* iterator;
	int decsendent_score;
	int extreme_score = (max ? -EXTREME_VALUE : EXTREME_VALUE);

	if ((current_node->children == NULL) || (depth == 0)
			|| (current_node->score == EXTREME_VALUE)
			|| (current_node->score == -EXTREME_VALUE)) {
		return current_node->score;
	}
	iterator = current_node->children->head;
	while (iterator != NULL) {
		decsendent_score = calculate_minmax(iterator->node, depth - 1, !max);
		if ((max && decsendent_score > extreme_score)
				|| (!max && decsendent_score < extreme_score)) {
			extreme_score = decsendent_score;
		}
		iterator = iterator->next;
	}
	return extreme_score;
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
            if (run_minmax_on_vertex(iterator->node, is_comp_turn)->score < min) {
                min = iterator->node->score;
                chosen_vertex = iterator->node;
            }
            iterator = iterator->next;
        }
        while (iterator->next != NULL);
    } else {
        do {
            if (run_minmax_on_vertex(iterator->node, is_comp_turn)->score > max) {
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
