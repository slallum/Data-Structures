#include <stdlib.h>
#include <stdio.h>

#include "tree.h"

/**
 * Initializes a new tree and builds it until requested depth.
 * User is always first so root will be his turn.
 */
minmax_tree* create_tree(Board* board, int depth, 
                         int (*make_move)(Board* board, Move* new_move, int value), 
                         int (*get_score)(Board* board)) {
    minmax_tree* tree;
    vertex* current_root;

    if ((tree = (minmax_tree*) calloc(1, sizeof(minmax_tree))) == NULL) {
        printf("Error: standard function malloc has failed");
        return NULL;
    }

    if ((current_root = (vertex*)calloc(1, sizeof(vertex))) == NULL) {
        printf("Error: standard function malloc has failed");
        return NULL;
    }

    current_root->score = 0;
    current_root->current_move = (Move*) malloc(sizeof(Move));
    current_root->current_move->i = -1;
    current_root->current_move->j = -1;
    current_root->value = 1;
    current_root->children = NULL;
    extend(current_root, board, depth, make_move, get_score);

    tree->root = current_root;
    return tree;
}

/**
 * Updates root of tree according to col played
 *
 * @param   board - after performing move
 * @param   col - last chosen column
 * @param   row - last chosen row
 * @param   depth - max depth chosen
 */
void update_tree(minmax_tree *tree, Board* board, int col, int row, int depth) {
    element* iterator;
    vertex* current_root = tree->root;
    if (current_root->children != NULL) {
        iterator = current_root->children->head;
        while ((iterator->node->current_move->j != col) &&
               (iterator->node->current_move->i != row) &&
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
            remove_tree(current_root);
        }
    // no children - just change the root
    } else {
        tree->root->current_move->j = col;
        tree->root->current_move->i = row;
        tree->root->value = (-1) * (tree->root->value);
    }
 }

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
                       int (*get_score)(Board* board)) {
    int i;
    int unimplemented_moves_length;
    int current_score;

    if (depth == 0) {
        best_move->i = node->current_move->i;
        best_move->j = node->current_move->j;
        return node->score;
    }
    // if we don't have a linked list, but the depth isn't 0, we'll create an empty linked list
    if (node->children == NULL) {
        if ((node->children = (linked_list*)calloc(1, sizeof(linked_list))) == NULL) {
            printf("Error: standard function calloc has failed");
            exit(1);
        }
        node->children->head = NULL;
        node->children->tail = NULL;
    }


    element *iterator = node->children->head;
    Move *unimplemented_moves = get_unimplemented_moves(node->children, board, &unimplemented_moves_length, max,
                                                        make_move, undo_move);
    // runs max
    if (max) {
        while (iterator != NULL) {
            make_move(board, iterator->node->current_move, max ? FIRST_PL_TURN:SECOND_PL_TURN);
            current_score = minmax_with_extend(iterator->node, depth-1, alpha, beta, !max, board,
                                               make_move, undo_move, get_score);
            undo_move(board, iterator->node->current_move);
            if (current_score > alpha) {
                alpha = current_score;
                // update the best move accordingly
                best_move->i = node->current_move->i;
                best_move->j = node->current_move->j;
            }
            // alpha-beta pruning
            if (beta <= alpha) {
                return alpha;
            }
        }
        for (i=0; i<unimplemented_moves_length; i++) {
            add_node_to_end(node->children, unimplemented_moves[i], board, max ? FIRST_PL_TURN:SECOND_PL_TURN);
            // still need to update the score of the node. so we'll make the move and then update the score.
            make_move(board, node->children->tail->node->current_move, node->children->tail->node->value);
            node->children->tail->node->score = get_score(board);

            // now for the minmax part
            current_score = minmax_with_extend(node->children->tail->node, depth-1, alpha, beta, !max, board,
                                               make_move, undo_move, get_score);
            undo_move(board, node->children->tail->node->current_move);
            if (current_score > alpha) {
                alpha = current_score;
                // update the best move accordingly
                best_move->i = node->current_move->i;
                best_move->j = node->current_move->j;
            }
            // alpha-beta pruning
            if (beta <= alpha) {
                return alpha;
            }
        }
        return alpha;
    // runs min
    } else {
        while (iterator != NULL) {
            make_move(board, iterator->node->current_move, max ? FIRST_PL_TURN:SECOND_PL_TURN);
            current_score = minmax_with_extend(iterator->node, depth-1, alpha, beta, !max, board,
                                               make_move, undo_move, get_score);
            undo_move(board, iterator->node->current_move);
            if (current_score < beta) {
                beta = current_score;
                // update the best move accordingly
                best_move->i = node->current_move->i;
                best_move->j = node->current_move->j;
            }
            // alpha-beta pruning
            if (beta <= alpha) {
                return beta;
            }
        }
        for (i=0; i<unimplemented_moves_length; i++) {
            add_node_to_end(node->children, unimplemented_moves[i], board, max ? FIRST_PL_TURN:SECOND_PL_TURN);
            // still need to update the score of the node. so we'll make the move and then update the score.
            make_move(board, node->children->tail->node->current_move, node->children->tail->node->value);
            node->children->tail->node->score = get_score(board);

            // now for the minmax part
            current_score = minmax_with_extend(node->children->tail->node, depth-1, alpha, beta, !max, board,
                                               make_move, undo_move, get_score);
            undo_move(board, node->children->tail->node->current_move);
            if (current_score > beta) {
                beta = current_score;
                // update the best move accordingly
                best_move->i = node->current_move->i;
                best_move->j = node->current_move->j;
            }
            // alpha-beta pruning
            if (beta <= alpha) {
                return beta;
            }
        }
        return beta;
    }
}

/*
 * adds a node with the given move to the end of the linked list
 */
int add_node_to_end(linked_list *nodes_list, Move move, Board *board, int value) {
    element *new_element;
    vertex *node;

    if ((new_element = (element*)calloc(1, sizeof(element))) == NULL) {
        printf("Error: standard function calloc has failed");
        return 0;
    }

    if ((new_element->node = (vertex*)calloc(1, sizeof(vertex))) == NULL) {
        printf("Error: standard function calloc has failed");
        return 0;
    }
    if ((new_element->node->current_move = (Move*)malloc(sizeof(Move))) == NULL) {
        printf("Error: standard function malloc has failed");
        return 0;
    }
    new_element->node->current_move->i = move->i;
    new_element->node->current_move->j = move->j;
    new_element->node->value = value;
    
    // update the linked list
    new_element->next = NULL;
    // if the list is empty
    if (nodes_list->head == NULL) {
        nodes_list->head = new_element;
        nodes_list->tail = new_element;
        new_element->prev = NULL;
        return 1;
    }
    // any other case than an empty list
    nodes_list->tail->next = new_element;
    new_element->prev = nodes_list->tail;
    // update to the new tail
    nodes_list->tail = new_element;
    return 1;
}

/* 
 * returns an array of moves that can be made but don't exist in the nodes list
 */
Move *get_unimplemented_moves(linked_list *nodes_list, Board *board, int *new_length, int max,
                              int (*make_move)(Board* board, Move* new_move, int value), 
                              int (*undo_move)(Board* board, Move* new_move)) {
    int i, j;
    Move *result;
    Move current_move = {.i = 0, .j = 0};
    int result_index = 0;
    if ((result = (Move*)calloc(board->n*board->m, sizeof(Move))) == NULL) {
        printf("Error: unable to init moves list in get_unimplemented_moves.\n");
        return NULL
    }

    for (i=0; i < (board->n); i++) {
        for (j=0; j < board->m; j++) {
            current_move = {.i = i, .j = j};
            // if this move doesn't exist in the linked list - add it to result
            if (!move_in_linked_list(current_move, nodes_list)) {
                if (make_move(board, current_move, max ? FIRST_PL_TURN:SECOND_PL_TURN) != -1){
                    // first - undo the unnecessary move
                    undo_move(board, current_move);
                    
                    // add the move to the result
                    result[result_index] = Move(.i=current_move.i, .j=current_move.j);
                    result_index++;
                }
            }
        }
    }

    if (result = (Move*)(realloc(result, sizeof(Move)*result_index))) == NULL) {
        printf("Error: can't allocate result in get_unimplemented_moves.\n");
        return NULL;
    }
    *new_length = result_index;
    return result;
}

/*
 * returns True if a move exists in the list of nodes, False o/w.
 */
int move_in_linked_list(Move move, linked_list *nodes_list) {
    element *iterator = nodes_list->head;
    while (iterator != NULL) {
        if ((iterator->node->current_move->i == move.i) && (iterator->node->current_move->j == move.j)) {
            return 1;
        }
        iterator = iterator->next;
    }
    return 0;
}

/**
 * Frees all vertexts, elements, lists under node, recursively
 *
 */
void remove_tree(vertex* current_node) {

    element* previous;
    element* nextush;
    if ((current_node != NULL) && (current_node->children != NULL)) {
    	free(current_node->current_move);
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
