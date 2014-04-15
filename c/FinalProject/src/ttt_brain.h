/*
 * ttt_brain.h
 *
 *  Created on: Apr 10, 2014
 *      Author: shir
 */

#ifndef TTT_BRAIN_H_
#define TTT_BRAIN_H_

#include "game_framework.h"
#include "board.h"
#include "tree.h"
#include "playit_conf.h"

/**
 * Creates a new game specific for tic-tac-toe,
 * with all needed parameters
 */
Game *ttt_new_game();

/**
 * No need for special preparation
 */
void ttt_init_board(Board* board);

int ttt_is_valid_move(Board *board, Move *move, int value);

/*
 *
 * @param board		Current board of the game
 * @param new_move	Indexes in board requested as next move (by some player)
 * @param value		Value for the played move, indicating the player
 *
 * @return	-1 if cell is already taken by some player
 * 			 0 if move was made
 */
int ttt_make_move(Board* board, Move* new_move, int value);

/*
 * If there are adjacent cells with same symbol,
 * corresponding player wins
 */
int ttt_won_game(Game* game);

/*
 * If there are adjacent cells with same symbol,
 * corresponding player wins
 */
int ttt_won_board(Board* board);

/**
 * Check if row i on board has all same symbol as value
 */
int check_horizontal(int i, Board* board, int value);

/**
 * Check if coloumn i on board has all same symbol as value
 */
int check_vertical(int i, Board* board, int value);

/**
 * Check if main diagonal (i.e. identical row and coloumn)
 * has all same symbol as value
 */
int check_main_diag(Board* board, int value);

/**
 * Check if main diagonal (i.e. decreasing row and increasing coloumn)
 * has all same symbol as value
 */
int check_sec_diag(Board* board, int value);

/**
 * Tic Tac Toe AI is so clever, it can see until
 * last move of the game.
 * Therefore, need to indicate only winning board
 */
int ttt_get_score(Board* board);


#endif /* TTT_BRAIN_H_ */
