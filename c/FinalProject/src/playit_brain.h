/*
 * playit_brain.h
 *
 *  Created on: Mar 13, 2014
 *      Author: shir
 */

#ifndef PLAYIT_BRAIN_H_
#define PLAYIT_BRAIN_H_

#include "connect4_brain.h"
#include "ttt_brain.h"
#include "reversi_brain.h"
#include "playit_conf.h"
#include <string.h>

/**
 * Switches players from current to other (flips marks)
 * If currently playing is an AI player, returns 1,
 * indicating to continue fictive clicking, without waiting for user.
 */
int switch_player(Game* game);

/**
 * Tries all moves on the board for given player,
 * until meeting one that is possible.
 * Erases each move been made.
 */
int no_moves(Game* game, int player);

/**
 * Handles all logic around making a move in the game.
 * Updates the tree for all players and get
 *
 * @return	 0 - All went well, move was made and turn should pass on
 * 			-1 - Move was not made and turn should not pass (was illegal for player)
 * 			 1 - Move was made but current player is AI, so no waiting for user
 *
 */
int handle_move(Game* game, int i, int j);

/**
 * Saves required parameters of the game in required format
 * to a file, in order to allow retrieving.
 *
 * @param file_num	Number of file to save game to
 * @param game		Game struct that should contain current state
 */
int save_game(int file_num, Game* game);

/**
 * Reads the file according to required format and
 * saves each fo the paremeters in the game struct.
 *
 * @param file_num	Number of file to load game from
 * @return	Game struct with state as read from file
 */
Game* load_game(int file_num);

/**
 * If rc < 0, means there was an IO error,
 * either reading or writing.
 * Outputs suitable message.
 */
void check_validity(int rc);

#endif /* PLAYIT_BRAIN_H_ */
