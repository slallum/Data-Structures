#ifndef GAME_FRAMEWORK_H_
#define GAME_FRAMEWORK_H_

#include "board.h"
#include "tree.h"

typedef struct game_s {
    Board *board;

    int is_first_players_turn;
    int first_player_ai;
    int second_player_ai;
    int game_over;

    // rules
    int** (*available_moves)(struct game_s*);
    int (*make_move)(int**, int, int, int);
    int (*won_board)(struct game_s*);
    
    // minmax tree
    int (*get_score)(int**, int, int);
    int depth;
    minmax_tree *tree;
    int *difficulties;
} Game;

void free_game(Game *game);

Game *init_game();

#endif /* GAME_FRAMEWORK_H_ */
