#ifndef CONNECT4_BRAIN_H_
#define CONNECT4_BRAIN_H_

#include "game_framework.h"
#include "board.h"
#include "tree.h"
#include "playit_conf.h"

/**
 * Creates a new game specific for connect4,
 * with all needed parameters
 */
Game *connect4_new_game();

/**
 * Nothing special to do
 */
void connect4_init_board(Board* board);

/*
 * returns if the given move with the given value is valid on the given board
 */
int connect4_is_valid_move(Board *board, Move *new_move, int value);

/*
 * Gets cells, height of cells, column to insert and a value to insert
 * makes the move, according to connect4 laws
 * returns the row of the changed cell
 * if the column is full - returns -1
 * Otherwise, if move was made, returns 0
 */
int connect4_make_move(Board* board, Move* new_move, int value);

/*
 * Checks if the board has a winning streak (player doesn't matter).
 * Checks spans in each direction.
 * Once finding a winning span, changes their value to winning value.
 */
int connect4_won_game(Game* game);

/**
 * Checks if in any span on board there is a
 * 4-some, four adjacent, same player discs
 *
 * @param board	Current board state
 * @param start	Indexes for starting i and j in matrix
 * @param end	Indexes for ending i and j in matrix
 * @param dir	Indexes for directions of i and j (1, 0, -1)
 */
int check_spans(Board* board, int start[2], int end[2], int dir[2]);

/**
 * Scoring function for the connect4 game
 * Each 4 disc span recieves a score and the number
 * of spans for each score are calculated.
 * The outcome vector is multiplied by a weight vector
 */
int connect4_get_score(Board* board);

/**
 * Goes over all horizontal spans on board.
 * For each row, calcs first span and then just updates each step
 */
void count_horizontal(int *spans_count, int** board, int n, int m);

/**
 * Goes over all vertical spans on board.
 * For each coloumn, calcs first span and then just update each step.
 */
void count_vertical(int *spans_count, int** board, int n, int m);

/**
 * Goes over all vertical spans on board.
 * For each coloumn, calcs first span and then just update each step.
 */
void count_diagonal(int *spans_count, int** board, int n, int m);

#endif /* CONNECT4_BRAIN_H_ */
