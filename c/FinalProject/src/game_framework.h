#ifndef GAME_FRAMEWORK_H_
#define GAME_FRAMEWORK_H_

#include "board.h"
#include "tree.h"

typedef struct game_s {
    Board *board;

    int is_first_players_turn;
    int first_player_ai;
    int first_player_depth;
    int second_player_ai;
    int second_player_depth;
    int game_over;

    // rules
    int** (*available_moves)(struct game_s*);
    int (*make_move)(Board* board, Move* new_move, int value);
    int (*won_board)(Board* board);
    
    // minmax tree
    int (*get_score)(Board* board);
    minmax_tree *tree;
    int max_depth;

    char* tiles[3];
} Game;

void free_game(Game *game);

Game *init_game();

#endif /* GAME_FRAMEWORK_H_ */
