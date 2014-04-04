#ifndef TREE_H_
#define TREE_H_

#include "board.h"
#include "playit_conf.h"


// Linked list element
typedef struct element_s {
    struct vertex_s     *node;
    struct element_s    *next;
    struct element_s    *prev;
} element;

// Linked list
typedef struct linked_list_s {
    struct element_s *head;
    struct element_s *tail;
} linked_list;

// Tree vertex holding data
typedef struct vertex_s {
//    Board         game_state;
    int             score;
    // The move that leads to this node
    Move*           current_move;
    int				value;
    linked_list     *children;
} vertex;

// Tree represented by root
typedef struct minmax_tree_s {
    vertex *root;
    int (*make_move)(Board* board, Move* new_move, int value);
    int (*scoring_func)(Board* board);
} minmax_tree;


/**
 * Initializes a new tree and builds it until requested depth.
 * User is always first so root will be his turn.
 */
minmax_tree* create_tree(Board* board, int depth,
		int (*make_move)(Board* board, Move* new_move, int value), int (*get_score)(Board* board));

/**
 * Adds levels to tree until reaching requested depth
 */
void update_tree(minmax_tree *tree, Board* board, int col, int depth);


/* --- Helper Methods --- */

/**
 * Receives a leaf in the tree and extends it with all options for moves.
 * Recursively extends children created, until completing depth (i.e. remaining depth is 0)
 *
 */
void extend(vertex* current_node, Board* board, int depth,
		int (*make_move)(Board* board, Move* new_move, int value), int (*get_score)(Board* board));


/**
 * Frees all vertexts, elements, lists under requested node, recursively
 */
void remove_tree(vertex* node);

/**
 * Goes recursively down tree, thile building the appropriate boards.
 * When reaching a leaf, performs extension of the tree.
 */
void extend_leafs(vertex* current_node, Board* board, int depth,
		int (*make_move)(Board* board, Move* new_move, int value),int (*get_score)(Board* board));

#endif /* TREE_H_ */
