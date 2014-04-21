#include <stdlib.h>
#include <stdio.h>

#include "tree.h"
#include "board.h"

/**
 * Initializes a new tree and builds it until requested depth.
 * User is always first so root will be his turn.
 */
minmax_tree* create_tree(Board* board, int (*get_score)(Board* board)) {
    minmax_tree* tree;
    vertex* current_root;

    if ((tree = (minmax_tree*) calloc(1, sizeof(minmax_tree))) == NULL) {
        printf("ERROR: standard function malloc has failed\n");
        return NULL;
    }

    if ((current_root = (vertex*)calloc(1, sizeof(vertex))) == NULL) {
        printf("ERROR: standard function malloc has failed\n");
        return NULL;
    }

    current_root->score = get_score(board);
    if ((current_root->current_move = (Move*) malloc(sizeof(Move))) == NULL) {
        printf("ERROR: standard function malloc has failed\n");
        return NULL;
    }
    current_root->current_move->i = -1;
    current_root->current_move->j = -1;
    current_root->value = 1;
    current_root->children = NULL;

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
void update_tree(minmax_tree *tree, int col, int row, int depth) {
    element* iterator;
    vertex* current_root = tree->root;
    if (current_root->children != NULL) {
        iterator = current_root->children->head;
        while ((iterator != NULL) &&
               (!((iterator->node->current_move->j == col) &&
                  (iterator->node->current_move->i == row) ))) {
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
                       int (*get_score)(Board* board)) {
    int i;
    int unimplemented_moves_length;
    int current_score;
    Move *next_best_move;
    Board *copied_board = new_board(board->n, board->m);
    if (copied_board == NULL) {
        printf("ERROR: can't initiazlie copied board.\n");
        exit(1);
    }

    // we stop if we got to a winning move or the requested depth
    if ((depth == 0) || (node->score == EXTREME_VALUE) || (node->score == -EXTREME_VALUE)) {
        free_board(copied_board);
        return node->score;
    }
    // if we don't have a linked list, but the depth isn't 0, we'll create an empty linked list
    if (node->children == NULL) {
        if ((node->children = (linked_list*)malloc(sizeof(linked_list))) == NULL) {
            printf("ERROR: standard function malloc has failed\n");
            exit(1);
        }
        node->children->head = NULL;
        node->children->tail = NULL;
    }

    if ((next_best_move = (Move*)malloc(sizeof(Move))) == NULL) {
        printf("ERROR: malloc has failed in minmaxtree\n");
        exit(1);
    }

    element *iterator = node->children->head;
    Move *unimplemented_moves = get_unimplemented_moves(node->children, board, &unimplemented_moves_length, max,
                                                        is_valid_move);
    // we'll initialize best_move to SOME move, just in case EVERY move is a losing move.
    if (iterator != NULL) {
        best_move->i = iterator->node->current_move->i;
        best_move->j = iterator->node->current_move->j;
    } else {
        if (unimplemented_moves_length > 0) {
            best_move->i = unimplemented_moves[0].i;
            best_move->j = unimplemented_moves[0].j;
        // NO MOVES AT ALL - we don't care about the best move, just return the current score.
        } else {
            free_board(copied_board);
            free(next_best_move);
            free(unimplemented_moves);
            return node->score;
        }
    }

    // runs max
    if (max) {
        while (iterator != NULL) {
            copy_board(board, copied_board);
            make_move(copied_board, iterator->node->current_move, max ? FIRST_PL_TURN:SECOND_PL_TURN);
            current_score = minmax_with_extend(iterator->node, depth-1, alpha, beta, !max, copied_board, next_best_move,
                                               is_valid_move, make_move, get_score);
            // get the maximum of alpha and current score
            if (current_score > alpha) {
                alpha = current_score;
                // update the best move accordingly
                best_move->i = iterator->node->current_move->i;
                best_move->j = iterator->node->current_move->j;
                
                // alpha-beta pruning
                if (beta <= alpha) {
                    free_board(copied_board);
                    free(next_best_move);
                    free(unimplemented_moves);
                    return alpha;
                }
            }
            iterator = iterator->next;
        }
        for (i=0; i<unimplemented_moves_length; i++) {
            copy_board(board, copied_board);
            add_node_to_end(node->children, unimplemented_moves[i], copied_board, max ? FIRST_PL_TURN:SECOND_PL_TURN);
            // still need to update the score of the node. so we'll make the move and then update the score.
            make_move(copied_board, node->children->tail->node->current_move, node->children->tail->node->value);
            node->children->tail->node->score = get_score(copied_board);

            // now for the minmax part
            current_score = minmax_with_extend(node->children->tail->node, depth-1, alpha, beta, !max, copied_board, next_best_move,
                                               is_valid_move, make_move, get_score);
            // get the maximum of alpha and current score
            if (current_score > alpha) {
                alpha = current_score;
                // update the best move accordingly
                best_move->i = node->children->tail->node->current_move->i;
                best_move->j = node->children->tail->node->current_move->j;

                // alpha-beta pruning
                if (beta <= alpha) {
                    free_board(copied_board);
                    free(next_best_move);
                    free(unimplemented_moves);
                    return alpha;
                }
            }
        }
        free_board(copied_board);
        free(next_best_move);
        free(unimplemented_moves);
        return alpha;
    // runs min
    } else {
        while (iterator != NULL) {
            copy_board(board, copied_board);
            make_move(copied_board, iterator->node->current_move, max ? FIRST_PL_TURN:SECOND_PL_TURN);
            current_score = minmax_with_extend(iterator->node, depth-1, alpha, beta, !max, copied_board, next_best_move,
                                               is_valid_move, make_move, get_score);
            // get the minimum of beta and current score
            if (current_score < beta) {
                beta = current_score;
                // update the best move accordingly
                best_move->i = iterator->node->current_move->i;
                best_move->j = iterator->node->current_move->j;
                
                // alpha-beta pruning
                if (beta <= alpha) {
                    free_board(copied_board);
                    free(next_best_move);
                    free(unimplemented_moves);
                    return beta;
                }
            }
            iterator = iterator->next;
        }
        for (i=0; i<unimplemented_moves_length; i++) {
            copy_board(board, copied_board);
            add_node_to_end(node->children, unimplemented_moves[i], copied_board, max ? FIRST_PL_TURN:SECOND_PL_TURN);
            // still need to update the score of the node. so we'll make the move and then update the score.
            make_move(copied_board, node->children->tail->node->current_move, node->children->tail->node->value);
            node->children->tail->node->score = get_score(copied_board);

            // now for the minmax part
            current_score = minmax_with_extend(node->children->tail->node, depth-1, alpha, beta, !max, copied_board, next_best_move,
                                               is_valid_move, make_move, get_score);
            // get the minimum of beta and current score
            if (current_score < beta) {
                beta = current_score;
                // update the best move accordingly
                best_move->i = node->children->tail->node->current_move->i;
                best_move->j = node->children->tail->node->current_move->j;

                // alpha-beta pruning
                if (beta <= alpha) {
                    free_board(copied_board);
                    free(next_best_move);
                    free(unimplemented_moves);
                    return beta;
                }
            }
        }
        free_board(copied_board);
        free(next_best_move);
        free(unimplemented_moves);
        return beta;
    }
}

/*
 * adds a node with the given move to the end of the linked list
 */
int add_node_to_end(linked_list *nodes_list, Move move, Board *board, int value) {
    element *new_element;

    if ((new_element = (element*)calloc(1, sizeof(element))) == NULL) {
        printf("ERROR: standard function calloc has failed\n");
        return 0;
    }

    if ((new_element->node = (vertex*)calloc(1, sizeof(vertex))) == NULL) {
        printf("ERROR: standard function calloc has failed\n");
        return 0;
    }
    if ((new_element->node->current_move = (Move*)malloc(sizeof(Move))) == NULL) {
        printf("ERROR: standard function malloc has failed\n");
        return 0;
    }
    new_element->node->current_move->i = move.i;
    new_element->node->current_move->j = move.j;
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
                              int (*is_valid_move)(Board* board, Move* new_move, int value)) {
    int i, j;
    Move *result;
    Move move = {.i = 0, .j = 0};
    int result_index = 0;
    if ((result = (Move*)calloc(board->n*board->m, sizeof(Move))) == NULL) {
        printf("ERROR: unable to init moves list in get_unimplemented_moves.\n");
        return NULL;
    }

    for (i=0; i < (board->n); i++) {
        for (j=0; j < board->m; j++) {
            move.i = i;
            move.j = j;
            // if this move doesn't exist in the linked list - add it to result
            if (!move_in_linked_list(move, nodes_list)) {
                // check that it is a valid move.
                // `is_valid_move` function can CHANGE the move coordinates,
                // and we only want moves that don't change their coordinates
                if (is_valid_move(board, &move, max ? FIRST_PL_TURN:SECOND_PL_TURN) &&
                    ((move.i == i) && (move.j == j)) ){
                    // add the move to the result
                    result[result_index] = (Move){.i=move.i, .j=move.j};
                    result_index++;
                }
            }
        }
    }
    *new_length = result_index;
    if (result_index == 0) {
        free(result);
        return NULL;
    }

    // we now know how manu unimplemented moves we have - so we rellocate te memory to fit it.
    if ((result = (Move*)(realloc(result, sizeof(Move)*result_index))) == NULL) {
        printf("ERROR: can't allocate result in get_unimplemented_moves.\n");
        exit(1);
    }
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
