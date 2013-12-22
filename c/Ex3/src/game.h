#ifndef GAME_H_
#define GAME_H_

#include "tree.h"
#include "board.h"

typedef struct game_s {
    board_t current_board;
    int is_comp_turn;
    minmax_tree *tree;
    int depth;
} game;

void make_user_move(game *current_game, int move_column);

int make_comp_move(game *current_game);

int make_connect4_move(int** cells, int n, int i, int value);

#endif /* GAME_H_ */
