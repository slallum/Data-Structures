/*
 * playit_manager.h
 *
 *  Created on: Mar 13, 2014
 *      Author: shir
 */

#ifndef PLAYIT_MANAGER_H_
#define PLAYIT_MANAGER_H_

#include "gui_framework.h"
#include "playit_brain.h"
#include "playit_gui.h"

/**
 * Handle button 'New Game' click.
 * Moves to game selection screen.
 *
 * @param	The button object
 */
int on_new_game(Control* btn_new_game);

/**
 * Handle button 'Load Game' click.
 * Moves to file selection screen.
 */
int on_load_game(Control* btn_load_game);

/**
 * Handle button 'Quit'.
 * Closes window.
 */
int on_select_quit(Control* btn_quit);

/**
 * Handles choice of a ttt game.
 * Moves to selecting type of players.
 */
int on_select_tictactoe(Control* btn_game);

/**
 * Handles choice of reversi game.
 * Moves to selecting type of players.
 */
int on_select_reversi(Control* btn_game);

/**
 * Handles choice of connect4 game.
 * Moves to selecting type of players.
 */
int on_select_connect4(Control* btn_game);


/**
 * Returns to main menu without creating game.
 */
int on_cancel(Control* btn_game);

/**
 * Sets current game with player as first and second.
 */
int on_select_pl_pl(Control* btn_pl_type);

/**
 * Sets current game with player first and ai second.
 */
int on_select_pl_ai(Control* btn_pl_type);

/**
 * Sets current game with ai first and second.
 */
int on_select_ai_ai(Control* btn_pl_type);

/**
 * Sets current game with ai first and player second.
 */
int on_select_ai_pl(Control* btn_pl_type);

/**
 * Handles selection of a tile on the board.
 * Performs corresponding move according to stated by
 * current game rules.
 */
int on_select_tile(Control* btn_tile);

/**
 * Start new game with exact same parameters as current.
 */
int on_select_restart(Control* btn);

/**
 * Save current game state to a file, without stopping the game.
 */
int on_select_save(Control* btn);

/**
 * Change to main menu window.
 */
int on_select_main(Control* btn);

/**
 * Climb to the root of the tree
 */
Control* get_root(Control* control);

#endif /* PLAYIT_MANAGER_H_ */
