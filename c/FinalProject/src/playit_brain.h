/*
 * playit_brain.h
 *
 *  Created on: Mar 13, 2014
 *      Author: shir
 */

#ifndef PLAYIT_BRAIN_H_
#define PLAYIT_BRAIN_H_

#include "connect4_brain.h"
#include "playit_conf.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Switches players from current to other (flips marks)
 * If currently playing is an AI player, returns 1,
 * indicating to continue fictive clicking, without waiting for user.
 */
int switch_player(Game* game);

/**
 * Handles all logic around making a move in the game.
 * Updates the tree for all players and get
 *
 * @return	 0 - All went well, move was made and turn should pass on
 * 			-1 - Move was not made and turn should not pass (was illegal for player)
 * 			 1 - Move was made but turn should not pass (next player has no illegal moves)
 *
 */
int handle_move(Game* game, int i, int j);

/**
 * If at least one cell in the board has no value in it,
 * return false - means there are more moves
 */
int board_full(Game* game);

/**
 * Saves required parameters of the game in required format
 * to a file, in order to allow retrieving.
 *
 * @param file_num	Number of file to save game to
 * @param game		Game struct that should contain current state
 */
int save_game(int file_num, Game* game, char* game_name);

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
