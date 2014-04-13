#ifndef GAME_FRAMEWORK_H_
#define GAME_FRAMEWORK_H_

#include "board.h"
#include "tree.h"

typedef struct game_s {
    Board *board;

    char* save_game_name;

    int is_first_players_turn;
    int first_player_ai;
    int first_player_depth;
    int second_player_ai;
    int second_player_depth;
    int game_over;

    // game logic
    void (*init_board)(Board* board);
    int (*make_move)(Board* board, Move* new_move, int value);
    int (*undo_move)(Board* board, Move* new_move);
    int (*won_game)(struct game_s*);
    
    // minmax tree
    int (*get_score)(Board* board);
    minmax_tree *tree;
    int depth_range[2];
    char* tiles[4];
} Game;

void free_game(Game *game);

Game *init_game();

#endif /* GAME_FRAMEWORK_H_ */
