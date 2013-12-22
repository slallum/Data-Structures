#ifndef TREE_H_
#define TREE_H_

#include "board.h"
#include "scoring.h"

#include <stdlib.h>

// Linked list element
typedef struct element_s {
    struct vertex_s     *node;
    struct element_s    *next;
    struct element_s    *prev;
} element;

// Linked list
typedef struct linked_list_s {
    element head;
    element tail;
} linked_list;

// Tree vertex holding data
typedef struct vertex_s {
//    board_t         game_state;
    int             score;
    // The move that leads to this node
    int             column_num;
    linked_list     children;
} vertex;

// Tree represented by root
typedef struct minmax_tree_s {
    vertex *root;
    int (*make_move)(board_t*, int, int);
    int (*scoring_func)(int**, int, int);
} minmax_tree;

/**
 * Initializes a new tree and builds it until requested depth.
 * User is always first so root will be his turn.
 */
minmax_tree* create_tree(board_t* board, int depth);

/**
 * Receives a leaf in the tree and extends it with all options for moves.
 * Recursively extends children created, until completing depth (i.e. remaining depth is 0)
 *
 */
void extend(vertex* node, board_t* board, int depth, int value);

/**
 * Adds levels to tree until reaching requested depth
 */
void update_tree(minmax_tree *tree, int depth, int is_comp_turn);

#endif /* TREE_H_ */
