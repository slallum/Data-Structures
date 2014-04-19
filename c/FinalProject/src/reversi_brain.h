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
#include "playit_conf.h"

/**
 * Creates a new game specific for tic-tac-toe,
 * with all needed parameters
 */
Game *reversi_new_game();

/**
 * Adds to the board 4 middle tiles that open the game
 */
void reversi_init_board(Board* board);

/**
 * Checks if given move is valid for given player,
 * denoted by value.
 * Doesn't change the board, just checks
 */
int reversi_is_valid_move(Board *board, Move *move, int value);

/*
 * Returns 0 if move is legal and was made.
 * Returns -1 Otherwise
 *
 * A legal move is one adjacent to some opponent's tile
 * Also, flips all oppoent's tiles in adjacent streaks
 */
int reversi_make_move(Board* board, Move* new_move, int value);

/**
 * Checks for the given direction, if it makes the given position a legal move.
 * This happens if tiles in that direction from position belong to opponent
 * and somewhere there is a tile belonging to current player.
 *
 * Also, performs the move by flipping all oponent's tiles, if found legal.
 */
int consider_move(Board* board, Move* position, Move* direction, int value, int change_board);

/*
 * checks if the board has a winning streak (the player who won doesn't matter)
 */
int reversi_won_game(Game* game);

/**
 * Checks for each cell on the board, if it is a possible
 * move for player 1 or for player 2 and updates the counts accordingly
 */
int* count_avail_moves(Board* board);

/**
 * Returns difference between
 * Number of Player 1 and number of Player 2
 * disks on given board
 */
int count_disk_parity(Board* board);

/**
 * Heuristic calculation follows:
 * weighted disk parity + 2 * available moves parity + 5 * stability parity
 */
int reversi_get_score(Board* board);

/**
 * According to simple scoring function (provided for project),
 * counts all values in board, multiplied by the weight
 * corresponding with their position on the board.
 */
int weighted_disk_parity(Board* board);

/**
 * Region 1 - the inner square of board
 * (minus 2 rows and 2 coloumns from top, bottom and sides)
 */
int count_reg_1(Board* board);

/**
 * Region 2 - second coloumns \ rows from edges,
 * except 2 first and 2 last cells
 *
 */
int count_reg_2(Board* board);

/**
 * Region 3 - first coloumns \ rows from edges,
 * except 2 first and 2 last cells.
 */
int count_reg_3(Board* board);

/**
 * Region 4 - three of each 4 corner cells (except corner cell)
 */
int count_reg_4(Board* board);

/**
 * Region 5 - corners
 */
int count_reg_5(Board* board);

/**
 * Counts the difference in the stability between first and second players,
 * where stability is the number of stable pieces.
 * A stable piece is one that can never be flipped again in the game.
 * This happens if piece is in the corner,
 * on edge with only same coloured pieces between it and a neighbour corner,
 * or in any position within a diagonal between two stable pieces.
 */
int count_stability_parity(Board* board);

/**
 * Checks if tiles are stable from the forner (i_start, j_start)
 * towards the corner (i_end, j_end) according to (i_dir, j_dir)
 */
int count_stability_section(Board* board, int i_start, int j_start,
		int i_end, int j_end, int i_dir, int j_dir);

/**
 * Copy each value of each cell in from_board
 * to the corresponding cell in to_board
 */
void reversi_copy_board(Board* from_board, Board* to_board);

#endif /* REVERSI_BRAIN_H_ */
