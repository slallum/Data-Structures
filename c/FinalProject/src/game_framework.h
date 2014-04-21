#ifndef GAME_FRAMEWORK_H_
#define GAME_FRAMEWORK_H_

#include "board.h"
#include "tree.h"

typedef struct game_s {
    Board *board;

    char* save_game_name;
    // game states
    int current_player;
    int game_over;
    // booleans
    int first_player_ai;
    int second_player_ai;
    // depths
    int first_player_depth;
    int second_player_depth;
    int depth_range[2];

    /* -- game logic -- */
    // init board gets an allocated board and initiazlies it if needed (e.g in Reversi - adds 4 discs in the middle)
    void (*init_board)(Board* board);
    // is_valid_move checks if a given move with a given value is valid on the given board
    int (*is_valid_move)(Board *board, Move *move, int value);
    // make_move makes he given move with the given value ON the given board. (changes the board)
    // returns -1 if the move cannot be taken
    int (*make_move)(Board* board, Move* new_move, int value);
    // won_game checks if the game has won, and changes the state of the game if it over
    int (*won_game)(struct game_s*);
    
    /* -- minmax tree -- */
    // get_score gets a board and returns its score, for the minmax tree algorithm to use
    int (*get_score)(Board* board);
    minmax_tree *tree;
    char* tiles[4];
} Game;


// get the best move for the current game state, by the minmax algorithm with the current depth
// gets best_move pointer - that is already initialized
void get_best_move(Game *game, Move *best_move);

// return if the current player is AI or not
int current_player_is_ai(Game *game);

// restarts the game from the beginning (the game stays of the same type)
int restart_game(Game *game);

/**
 * Frees all memory allocated for the game object
 */
void free_game(Game *game);

#endif /* GAME_FRAMEWORK_H_ */
