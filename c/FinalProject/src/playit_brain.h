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

#endif /* PLAYIT_BRAIN_H_ */
