/*
 * tree.c
 *
 *  Created on: Dec 17, 2013
 *      Author: shir
 */

#include "tree.h"


/**
 * Initializes a new tree and builds it until requested depth.
 * User is always first so root will be his turn.
 */
minmax_tree* create_tree(board_t* board, int depth) {

	minmax_tree* tree = (minmax_tree*) malloc(sizeof(minmax_tree));
	vertex* root = (vertex*) malloc(sizeof(vertex));

	root->score = 0;
	root->column_num = 0;
	extend(root, board, depth, 1);

	tree->root = root;
	return tree;
}

/**
 * Receives a leaf in the tree and extends it with all options for moves.
 * Recursively extends children created, until completing depth (i.e. remaining depth is 0)
 *
 */
void extend(vertex* node, board_t* board, int depth, int value) {

	int i, move;
	linked_list* children;
	element* iterator;
	vertex* child;

	if (depth == 0) {
		return;
	}
	children = (linked_list*) malloc(sizeof(linked_list));
		for (i = 0; i < board->m; i++) {
		move = execute_move(board, i, value);
		if (move != 0) {
			iterator = (element*) malloc(sizeof(element));
			child = (vertex*) malloc(sizeof(vertex));
			child->column_num = i;
			child->score = get_score(board);
		}
	}
}



/**
 * Adds levels to tree until reaching requested depth
 */
void update_tree(minmax_tree *tree, int depth, int is_comp_turn) {

}
