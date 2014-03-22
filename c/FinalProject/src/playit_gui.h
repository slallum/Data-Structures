/*
 * playit_gui.h
 *
 *  Created on: Mar 1, 2014
 *      Author: shir
 */

#ifndef PLAYIT_GUI_H_
#define PLAYIT_GUI_H_

#include <stdio.h>
#include "gui_framework.h"
#include "playit_conf.h"
#include "playit_manager.h"

/**
 * Generically creates a vertical buttons menu.
 * Calculates the spaces between the buttons according to their number, widths and heights.
 */
Control* create_button_menu(int height, int width, int num, char* games[],
		int (*handles[])(Control*), int widths[], int heights[]);

/**
 * Builds the start menu screen, including 3 buttons for selection:
 * Start Game, Load Game, Quit
 */
int show_main_menu(Control* window);

/**
 * Build game menu, according to definition of containing games
 */
int show_game_menu(Control* window);

/**
 * Build list of possible players options
 */
int show_player_select(Control* window);

/**
 * Shows the screen with the selected game, according to request.
 * Includes game board, game options and general menu
 */
int show_game_arena(Control* window, Game *game);

/**
 * Build the side menu for the game window.
 */
Control* create_game_menu(int height, int width);

/**
 * Build the board view for the current game.
 */
Control* create_board(int width, int height, int n, int m, int** cells);

/**
 * Sets current empty, player 1 and player 2
 * tiles to match reversi game.
 */
void set_reversi_tiles();

/**
 * Sets current empty, player 1, and player 2
 * tiles to match tictactoe game
 */
void set_tictactoe_tiles();

/**
 * Sets current empty and players'
 * tiles to match the connect4 game
 */
void set_connect4_tiles();

/**
 * Clears current window - frees tree that window is its root
 */
void clear_window(Control* window);

#endif /* PLAYIT_GUI_H_ */
