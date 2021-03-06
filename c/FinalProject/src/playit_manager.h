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
#include "tree.h"

/* --- GUI handles --- */

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
 * According to i of the selected button,
 * updates the current player.
 * Note: Counts on the order of the players.
 *       New types can be added easily as long as in the end..
 */
int on_select_player(Control* btn_pl_type);

/**
 * When first player is AI, game arena starts paused
 * (first move is not made)
 * until clicking 'Resume'.
 * This is in order to allow setting difficulty
 */
int on_select_resume(Control* btn_tile);

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
 * Handles save of current game to selected file,
 * denoted by the i of the given file_btn
 */
int on_select_save_file(Control* file_btn);

/**
 * Handles save of current game to selected file,
 * denoted by the i of the given file_btn
 */
int on_select_load_file(Control* file_btn);

/**
 * Clicking difficulty from menu, sets stated value as current difficulty
 * for the corresponding player (according to btn position)
 */
int on_select_difficulty(Control* btn);

/* --- Inner methods --- */

/**
 * Increases the player's depth by 1, mod max.
 * Also, adds 1 because not zero-indexed
 *
 * @param curr	Address of player's game depth to increase
 * @param range	Min and max depth possible as set for the current game
 */
void next_level(int* curr, int range[]);

/**
 * Climb to the root of the tree
 */
Control* get_root(Control* control);

/**
 * Opens game screen for beginning of the game.
 * If first player is AI, opens it paused,
 * with a 'Resume' button.
 * This is in order to give the opportunity to change difficulty
 */
int show_arena(Control* window);


#endif /* PLAYIT_MANAGER_H_ */
