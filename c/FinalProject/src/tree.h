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
    int             score;
    // The move that leads to this node
    Move*           current_move;
    int				value;
    linked_list     *children;
} vertex;

// Tree represented by root
typedef struct minmax_tree_s {
    vertex *root;
} minmax_tree;


/**
 * Initializes a new tree and builds it until requested depth.
 * User is always first so root will be his turn.
 */
minmax_tree* create_tree(Board* board, int (*get_score)(Board* board));

/**
 * Adds levels to tree until reaching requested depth
 */
void update_tree(minmax_tree *tree, Board* board, int col, int row, int depth);


/**
 * runs minmax and extend at the same time
 * 
 * @param depth - the depth of the tree
 * @param max - do max or min?
 */
int minmax_with_extend(vertex *node, int depth, int alpha, int beta, int max,
                       Board *board, Move *best_move,
                       int (*make_move)(Board* board, Move* new_move, int value), 
                       int (*undo_move)(Board* board, Move* new_move),
                       int (*get_score)(Board* board));

/* --- Helper Methods --- */

/*
 * adds a node with the given move to the end of the linked list
 */
int add_node_to_end(linked_list *nodes_list, Move move, Board *board, int value);

/* 
 * returns an array of moves that can be made but don't exist in the nodes list
 */
Move *get_unimplemented_moves(linked_list *nodes_list, Board *board, int *new_length, int max,
                              int (*make_move)(Board* board, Move* new_move, int value), 
                              int (*undo_move)(Board* board, Move* new_move));

/*
 * returns True if a move exists in the list of nodes, False o/w.
 */
int move_in_linked_list(Move move, linked_list *nodes_list);





/**
 * Frees all vertexts, elements, lists under requested node, recursively
 */
void remove_tree(vertex* node);


#endif /* TREE_H_ */
