#ifndef GAME_FRAMEWORK_H_
#define GAME_FRAMEWORK_H_

#include "board.h"
#include "tree.h"

typedef struct game_s {
    Board *board;

    char* save_game_name;
    int current_player;
    int first_player_ai;
    int first_player_depth;
    int second_player_ai;
    int second_player_depth;
    int game_over;
    int depth_range[2];

    // game logic
    void (*init_board)(Board* board);
    int (*is_valid_move)(Board *board, Move *move, int value);
    int (*make_move)(Board* board, Move* new_move, int value);
    int (*won_game)(struct game_s*);
    
    // minmax tree
    int (*get_score)(Board* board);
    minmax_tree *tree;
    char* tiles[4];
} Game;

/**
 * Removes all dynamic memory allocated for the game
 */
void free_game(Game *game);

// get the best move for the current game state, by the minmax algorithm with the current depth
Move *get_best_move(Game *game);


// return if the current player is AI or not
int current_player_is_ai(Game *game);

Game *init_game();

int restart_game(Game *game);

#endif /* GAME_FRAMEWORK_H_ */
