#ifndef GAME_FRAMEWORK_H_
#define GAME_FRAMEWORK_H_

#include "board.h"
#include "tree.h"

#define AI_NOT_SET -1;

typedef struct game_s {
    Board board;

    int is_first_players_turn;
    int first_player_ai;
    int second_player_ai;
    int game_over;

    // rules
    // struct Game* (*new_game)();
    int** (*available_moves)(struct game_s*);
    int (*won_board)(struct game_s*);
    
    // minmax tree
    int depth;
    minmax_tree *tree;
    int *difficulties;
} Game;

void free_game(Game *game);

Game *init_game();

#endif /* GAME_FRAMEWORK_H_ */