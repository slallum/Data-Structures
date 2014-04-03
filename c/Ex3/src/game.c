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

static int get_best_coloumn(vertex* current_node, int depth, int max);
static int calculate_minmax(vertex* current_node, int depth, int max);


/*
 * creating a new game and putting it in the pointer current_game
 * returns 0 if a command has failed
 */
int new_game(game *current_game, int depth) {
    int **cells;
    int i;
    // allocate all the cells
    if ((cells = (int**)calloc(BOARD_HEIGHT, sizeof(int*))) == NULL) {
        perror("Error: standard function malloc has failed");
        return 0;
    }
    for (i=0; i<BOARD_HEIGHT; i++) {
        if ((cells[i] = (int*)calloc(BOARD_WIDTH, sizeof(int))) == NULL) {
            perror("Error: standard function malloc has failed");
            return 0;
        }
    }
    // create  the board
    board_t current_board = { cells, BOARD_HEIGHT, BOARD_WIDTH, &connect4_scoring, &make_connect4_move };

    current_game->current_board = current_board;
    current_game->is_comp_turn = 0;
    if (current_game->tree != NULL) {
    	remove_tree(current_game->tree->root);
    }
    // creating the tree
    // if depth not set yet - we'll create a tree with only 1 depth
    if (depth == DEPTH_NOT_SET) {
    	if ((current_game->tree = create_tree(&(current_game->current_board), 1)) == NULL) {
			return 0;
		}
    // depth is already set - create the the way it should be
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
    // check when we reach a non empty cell
	while ((j < n) && (cells[j][i] == 0)) {
		j++;
	}
    // if j IS 0 - it means that the column is full and we'll return -1
    // otherwise - we'll change the value in the cells and return the right row
	if (j != 0) {
		cells[j - 1][i] = value;
	}
	return j - 1;
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
    return get_best_coloumn(current_game->tree->root, current_game->depth, 0);
}

/*
 * gets the best column to insert a disc if the current player is the user
 */
int get_best_move_for_player(game *current_game) {
	return get_best_coloumn(current_game->tree->root, current_game->depth, 1);
}


/*
 * returns the best column to insert in the board accoring to its parameters and the tree
 * param tree_root: the root of the minmax tree
 * param depth - the depth of the game
 * param max - 1 if we want to do max to this level (user), 0 is we want to do min to this level (computer)
 */ 
static int get_best_coloumn(vertex* tree_root, int depth, int max) {
	element* iterator;
	int decsendent_score, best_coloumn;
	int extreme_score = (max ? -EXTREME_VALUE : EXTREME_VALUE);
    // if it's already a leaf or we reached the max depth or the score indicates there's already a winner - we can return
	if ((tree_root->children == NULL) || (depth == 0)
			|| (tree_root->score == EXTREME_VALUE)
			|| (tree_root->score == -EXTREME_VALUE)) {
		return -1;
	}

    // iterate on the children
	iterator = tree_root->children->head;
	while (iterator != NULL) {
		decsendent_score = calculate_minmax(iterator->node, depth - 1, !max);
		// If score more extreme than what we have up to now
		if ((max && decsendent_score > extreme_score)
				|| (!max && decsendent_score < extreme_score)) {
			extreme_score = decsendent_score;
			best_coloumn = iterator->node->column_num;
		}
		iterator = iterator->next;
	}
	return best_coloumn % BOARD_WIDTH;
}

/**
 *	Calculates optimal value according to algorithm we learned
 *	Goes recursively down to leafs of given root, takes best value
 *	between all leaves,
 *	[where best is according to given parameter - either min or max]
 *	then 'pumps' it up until root, while jumping between min \ max in each level.
 */
static int calculate_minmax(vertex* current_node, int depth, int max) {
	element* iterator;
	int decsendent_score;
    // decide the extreme score accoring to max value - 1 (user) or 0 (computer)
	int extreme_score = (max ? -EXTREME_VALUE : EXTREME_VALUE);


    // if it's already a leaf or we reached the max depth or the score indicates there's already a winner - we can return
	if ((current_node->children == NULL) || (depth == 0)
			|| (current_node->score == EXTREME_VALUE)
			|| (current_node->score == -EXTREME_VALUE)) {
		return current_node->score;
	}

    // iterator over the children
	iterator = current_node->children->head;
	while (iterator != NULL) {
        // recursive call with depth-1 and the opposite player
		decsendent_score = calculate_minmax(iterator->node, depth - 1, !max);
		if ((max && decsendent_score > extreme_score)
				|| (!max && decsendent_score < extreme_score)) {
			extreme_score = decsendent_score;
		}
		iterator = iterator->next;
	}
	return extreme_score;
}
