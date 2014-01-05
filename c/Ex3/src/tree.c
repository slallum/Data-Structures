/*
 * tree.c
 *
 *  Created on: Dec 17, 2013
 *      Author: shir
 */

#include <stdlib.h>

#include "tree.h"
#include "scoring.h"


/**
 * Initializes a new tree and builds it until requested depth.
 * User is always first so root will be his turn.
 */
minmax_tree *create_tree(board_t* board, int depth) {
	minmax_tree* tree;
	vertex* current_root;

	if ((tree = (minmax_tree*) calloc(1, sizeof(struct minmax_tree_s))) == NULL) {
		perror("Error: standard function malloc has failed");
		return NULL;
	}

	if ((current_root = (vertex*) malloc(sizeof(struct vertex_s))) == NULL) {
	 	perror("Error: standard function malloc has failed");
	 	return NULL;
	}

	current_root->score = 0;
	current_root->column_num = 0;
	current_root->value = 1;
	extend(current_root, board, depth);

	tree->root = current_root;
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

	element* iterator;
	vertex* current_root = tree->root;
	if (current_root->children != NULL) {
		iterator = current_root->children->head;
		while ((iterator->node->column_num != col) &&
				(iterator != NULL)) {
			iterator = iterator->next;
		}
		if (iterator != NULL) {
			tree->root = iterator->node;
			if (iterator->prev != NULL) {
				iterator->prev->next = iterator->next;
			} else {
				current_root->children->head = iterator->next;
			}
			if (iterator->next != NULL) {
				iterator->next->prev = iterator->prev;
			} else {
				current_root->children->tail = iterator->prev;
			}
//			remove_tree(current_root);
		}
	}
	extend_leafs(tree->root, board, depth);
}


/**
 * Goes recursively down tree, while building the appropriate boards.
 * When reaching a leaf, performs extension of the tree.
 */
void extend_leafs(vertex* current_node, board_t* board, int depth) {
	element* iterator;
	int move;
	if (current_node->children == NULL) {
		extend(current_node, board, depth);
	} else {
		iterator = current_node->children->head;
		while (iterator != NULL) {
			move = execute_move(board, board->n, iterator->node->column_num, current_node->value);
			if (move != -1) {
				extend_leafs(iterator->node, board, depth - 1);
				board->cells[move][iterator->node->column_num] = 0;
			}
			iterator = iterator->next;
		}
	}
}

/**
 * Receives a leaf in the tree and extends it with all options for moves.
 * Recursively extends children created, until completing depth (i.e. remaining depth is 0)
 *
 */
void extend(vertex* current_node, board_t* board, int depth) {
	int i, move;
	element* current;
	vertex* child;
	linked_list* current_children = (linked_list*) malloc(sizeof(linked_list));
	element* previous = (element*) malloc(sizeof(element));
	current_children->head = previous;
	current_node->children = current_children;
	// Extends per each possible move
	for (i = 0; i < board->m; i++) {
		move = execute_move(board, board->n, i, current_node->value);
		// Unless this coloumn is full
		if (move != -1) {
			child = (vertex*) malloc(sizeof(vertex));
			child->column_num = i;
			child->score = get_score(board);
			child->value = (-1)*(current_node->value);
			if ((child->score != EXTREME_VALUE) && (child->score != -EXTREME_VALUE) && (depth-1 > 0)) {
				// Recursively perform for children too
				extend(child, board, depth - 1);
			}
			previous->node = child;
			// Place element in list and link to next element
			current = (element*) malloc(sizeof(element));
			previous->next = current;
			current->prev = previous;
			previous = current;
			board->cells[move][i] = 0;
		}
	}
	current_children->tail = previous->prev;
	current_children->tail->next = NULL;
}

/**
 * Frees all vertexts, elements, lists under node, recursively
 *
 */
void remove_tree(vertex* current_node) {

	element* previous;
	element* nextush;
	if ((current_node != NULL) && (current_node->children != NULL)) {
		previous = current_node->children->head;
		while (previous != NULL) {
			remove_tree(previous->node);
			nextush = previous->next;
			free(previous);
			previous = nextush;
		}
		free(current_node->children);
	}
	free(current_node);
}
