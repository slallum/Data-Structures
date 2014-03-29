#include <stdlib.h>
#include <stdio.h>

#include "board.h"
#include "tree.h"

/**
 * Initializes a new tree and builds it until requested depth.
 * User is always first so root will be his turn.
 */
minmax_tree* create_tree(Board* board, int depth, int (*make_move)(int**, int, int, int), int (*get_score)(int**, int, int)) {
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
    current_root->column_num = 0;
    current_root->value = 1;
    extend(current_root, board, depth, make_move, get_score);

    tree->root = current_root;
    return tree;
}

/**
 * Goes recursively down tree, while building the appropriate boards.
 * When reaching a leaf, performs extension of the tree.
 */
void extend_leafs(vertex* current_node, Board* board, int depth, int (*make_move)(int**, int, int, int), int (*get_score)(int**, int, int)) {
    element* iterator;
    int move;
    if (current_node->children == NULL) {
        extend(current_node, board, depth, make_move, get_score);
    } else {
        iterator = current_node->children->head;
        while (iterator != NULL) {
            move = make_move(board->cells, board->n, iterator->node->column_num, current_node->value);
            if ((move != -1) && (depth - 1 > 0)) {
                extend_leafs(iterator->node, board, depth - 1, make_move, get_score);
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
void extend(vertex* current_node, Board* board, int depth, int (*make_move)(int**, int, int, int), int (*get_score)(int**, int, int)) {
    int i, move;
    element* current;
    vertex* child;
    linked_list* current_children;
    element* previous;

    if ((current_children = (linked_list*) calloc(1, sizeof(linked_list))) == NULL) {
        perror("Error: standard function calloc has failed");
        exit(1);
    }
    if ((previous = (element*) calloc(1, sizeof(element))) == NULL) {
        perror("Error: standard function calloc has failed");
        exit(1);
    }
    current_children->head = previous;
    current_node->children = current_children;
    // Extends per each possible move
    for (i = 0; i < board->m; i++) {
        move = make_move(board->cells, board->n, i, current_node->value);
        // Unless this coloumn is full
        if (move != -1) {
            if ((child = (vertex*) calloc(1, sizeof(vertex))) == NULL) {
                perror("Error: standard function calloc has failed");
                exit(1);
            }
            child->column_num = i;
            child->score = get_score(board->cells, board->n, board->m);
            child->value = (-1)*(current_node->value);
            if ((child->score != EXTREME_VALUE) && (child->score != -EXTREME_VALUE) && (depth-1 > 0)) {
                // Recursively perform for children too
                extend(child, board, depth - 1, make_move, get_score);
            }
            previous->node = child;
            // Place element in list and link to next element
            if ((current = (element*) calloc(1, sizeof(element))) == NULL) {
                perror("Error: standard function calloc has failed");
                exit(1);
            }
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