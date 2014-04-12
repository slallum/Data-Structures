/*
 * reversi_brain.h
 *
 *  Created on: Apr 10, 2014
 *      Author: shir
 */

#ifndef REVERSI_BRAIN_H_
#define REVERSI_BRAIN_H_

#include "game_framework.h"
#include "board.h"
#include "tree.h"
#include "playit_brain.h"
#include "playit_conf.h"

/**
 * Creates a new game specific for tic-tac-toe,
 * with all needed parameters
 */
Game *reversi_new_game();

/*
 * Returns 0 if move is legal and was made.
 * Returns -1 Otherwise
 *
 * A legal move is one adjacent to some opponent's tile
 * Also, flips all oppoent's tiles in adjacent streaks
 */
int reversi_make_move(Board* board, Move* new_move, int value);

/**
 * Adds to the board 4 middle tiles that open the game
 */
void reversi_init_board(Board* board);

/**
 * Checks for the given direction, if it makes the given position a legal move.
 * This happens if tiles in that direction from position belong to opponent
 * and somewhere there is a tile belonging to current player.
 *
 * Also, performs the move by flipping all oponent's tiles, if found legal.
 */
int consider_move(Board* board, Move* position, Move* direction, int value);

/*
 * checks if the board has a winning streak (the player who won doesn't matter)
 */
int reversi_won_game(Game* game);

/**
 *
 */
int reversi_get_score(Board* board);


#endif /* REVERSI_BRAIN_H_ */
