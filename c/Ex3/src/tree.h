#ifndef TREE_H_
#define TREE_H_

#include "board.h"

struct element_s {
    struct vertex_s     *node;

    struct element_s    *next;
    struct element_s    *prev;
};

typedef struct element_s *  element;


struct linked_list_s {
    element head;
    element tail;
};

typedef struct linked_list_s *  linked_list;

struct vertex_s {
    unsigned int    mov_col;
    board_t         game_state;
    int             score;
    // the move that leads to this node
    int             column_num;

    linked_list     edges;
};

typedef struct vertex_s * vertex;


typedef struct minmax_tree_s {
    vertex *root;
} minmax_tree;

void update_tree(minmax_tree *tree, int depth, int is_comp_turn);

#endif /* TREE_H_ */