#include "game_framework.h"


/*
 * returns the best column to insert in the board accoring to its parameters and the tree
 * param tree_root: the root of the minmax tree
 * param depth - the depth of the game
 * param max - 1 if we want to do max to this level (user), 0 is we want to do min to this level (computer)
 */ 
int get_best_coloumn(vertex* tree_root, int depth, int max) {
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



static int calculate_minmax(vertex* current_node, int depth, int alpha, int beta, int max) {
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

/**
 *	Calculates optimal value according to algorithm we learned
 *	Goes recursively down to leafs of given root, takes best value
 *	between all leaves,
 *	[where best is according to given parameter - either min or max]
 *	then 'pumps' it up until root, while jumping between min \ max in each level.
 */
/*static int calculate_minmax(vertex* current_node, int depth, int max) {
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
}*/