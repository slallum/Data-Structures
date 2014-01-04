/*
 * tree.c
 *
 *  Created on: Dec 17, 2013
 *      Author: shir
 */

#include <stdlib.h>

#include "tree.h"


/**
 * Initializes a new tree and builds it until requested depth.
 * User is always first so root will be his turn.
 */
minmax_tree *create_tree(board_t* board, int depth) {

	minmax_tree* tree;
	vertex* root;
	if ((tree = (minmax_tree*) malloc(sizeof(minmax_tree))) == NULL) {
		perror("Error: standard function malloc has failed");
		return NULL;
	}
	if ((root = (vertex*) malloc(sizeof(vertex))) == NULL) {
		perror("Error: standard function malloc has failed");
		return NULL;
	}

	root->score = 0;
	root->column_num = 0;
	root->value = 1;
	extend(root, board, depth);

	tree->root = root;
	return tree;
}

/**
 * Updates root of tree according to col played
 * Adds levels to tree until reaching requested depth
 *
 * @param	board - after performing move
 * @param	col - last chosen col
 * @param	depth - max depth chosen
 */
void update_tree(minmax_tree *tree, board_t* board, int col, int depth) {

	vertex* root = tree->root;
	element* iterator;
	if (root->children != NULL) {
		iterator = root->children->head;
		while ((iterator->node->column_num != col) &&
				(iterator != NULL)) {
			iterator = iterator->next;
		}
		if (iterator != NULL) {
			tree->root = iterator->node;
			iterator->prev->next = iterator->next;
			remove_tree(root);
		}
	}
	extend_leafs(tree->root, board, depth);
}


/**
 * Goes recursively down tree, while building the appropriate boards.
 * When reaching a leaf, performs extension of the tree.
 */
void extend_leafs(vertex* node, board_t* board, int depth) {
	element* iterator;
	int move;
	if (node->children == NULL) {
		extend(node, board, depth - 1);
	} else {
		iterator = node->children->head;
		while (iterator != NULL) {
			move = execute_move(board, board->n, iterator->node->column_num, iterator->node->value);
			extend_leafs(iterator->node, board, depth - 1);
			board->cells[move][iterator->node->column_num] = 0;
			iterator = iterator->next;
		}
	}
}

/**
 * Receives a leaf in the tree and extends it with all options for moves.
 * Recursively extends children created, until completing depth (i.e. remaining depth is 0)
 *
 */
void extend(vertex* node, board_t* board, int depth) {
	int i, move;
	linked_list* children = (linked_list*) malloc(sizeof(linked_list));
	element* previous = (element*) malloc(sizeof(element));
	element* next;
	vertex* child;
	children->head = previous;
	node->children = children;
	if (depth == 0) {
		//Done extending
		return;
	}
	// Extends per each possible move
	for (i = 0; i < board->m; i++) {
		move = execute_move(board, board->n, i, node->value);
		// Unless this coloumn is full
		if (move != 0) {
			child = (vertex*) malloc(sizeof(vertex));
			child->column_num = i;
			child->value = (-1)*(node->value);
			child->score = get_score(board);
			if ((child->score != EXTREME_VALUE) && (child->score != -EXTREME_VALUE)) {
				// Recursively perform for children too
				extend(child, board, depth - 1);
			}
			previous->node = child;
			// Place element in list and link to next element
			next = (element*) malloc(sizeof(element));
			previous->next = next;
			next->prev = previous;
			previous = next;
			board->cells[move][i] = 0;
		}
	}
	children->tail = previous->prev;
	children->tail->next = NULL;
}

/**
 * Frees all vertexts, elements, lists under node, recursively
 *
 */
void remove_tree(vertex* node) {

	element* prev;
	element* next;
	if (node->children != NULL) {
		prev = node->children->head;
		while (prev != NULL) {
			remove_tree(prev->node);
			free(prev->node);
			next = prev->next;
			free(prev);
			prev = next;
		}
		free(node->children);
	}
	free(node);
}
