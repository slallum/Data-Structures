#ifndef TREE_H_
#define TREE_H_

#include "board.h"
#include "playit_conf.h"


// Linked list element
typedef struct element_s {
    struct vertex_s *node;
    struct element_s *next;
    struct element_s *prev;
} element;

// Linked list
typedef struct linked_list_s {
    struct element_s *head;
    struct element_s *tail;
} linked_list;

// Tree vertex holding data
typedef struct vertex_s {
    int score;
    // The move that leads to this node
    Move* current_move;
    int value;
    linked_list *children;
} vertex;

// Tree represented by root
typedef struct minmax_tree_s {
    vertex *root;
} minmax_tree;


/**
 * Initializes a new tree with one node.
 */
minmax_tree* create_tree(Board* board, int (*get_score)(Board* board));

/**
 * Updates root of tree according to col played
 *
 * @param   board - after performing move
 * @param   col - last chosen column
 * @param   row - last chosen row
 * @param   depth - max depth chosen
 */
void update_tree(minmax_tree *tree, int col, int row, int depth);


/**
 * runs minmax algorithm, extends the tree at the same time.
 * decides what is the best move to perform according to the minmax algorithm (with alphabeta pruning)
 * 
 * @param node - the current root of the minmax tree
 * @param alpha - the current maximum we got (for alphabeta pruning)
 * @param beta - the current minimum we got (for alphabeta pruning)
 * @param depth - the depth of the tree
 * @param max - do max or min?
 * @param board - the current board
 * @param best_move - pointer that will contain the best move to make, AFTER the function finishes.
 * @param is_valid_move - function that decides if a move is valid
 * @param make_move - function that makes the move on the board
 * @param get_score - the scoring function for the current game
 */
int minmax_with_extend(vertex *node, int depth, int alpha, int beta, int max,
                       Board *board, Move *best_move,
                       int (*is_valid_move)(Board *board, Move *move, int value),
                       int (*make_move)(Board* board, Move* new_move, int value), 
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
                              int (*is_valid_move)(Board* board, Move* new_move, int value));

/*
 * returns True if a move exists in the list of nodes, False o/w.
 */
int move_in_linked_list(Move move, linked_list *nodes_list);


/**
 * Frees all vertexts, elements, lists under requested node, recursively
 */
void remove_tree(vertex* node);


#endif /* TREE_H_ */
