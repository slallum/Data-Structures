#include <stdlib.h>
#include <stdio.h>

#include "board.h"
#include "tree.h"

/**
 * Initializes a new tree and builds it until requested depth.
 * User is always first so root will be his turn.
 */
minmax_tree* create_tree(Board* board, int depth) {
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
    extend(current_root, board, depth);

    tree->root = current_root;
    return tree;
}
