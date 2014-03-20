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
int on_quit(Control* btn_quit);

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


#endif /* PLAYIT_MANAGER_H_ */
