#ifndef GAME_H_
#define GAME_H_

#include "tree.h"
#include "board.h"

#define BOARD_HEIGHT 6
#define BOARD_WIDTH 7

typedef struct game_s {
    board_t current_board;
    int is_comp_turn;
    minmax_tree *tree;
    int depth;
    int game_over;
} game;

game *new_game(int depth);

int make_connect4_move(int** cells, int n, int i, int value);

int *get_computer_move(game *current_game);


#endif /* GAME_H_ */
