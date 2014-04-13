/*
 * playit_gui.h
 *
 *  Created on: Mar 1, 2014
 *      Author: shir
 */

#ifndef PLAYIT_GUI_H_
#define PLAYIT_GUI_H_

#include "gui_framework.h"
#include "game_framework.h"
#include "playit_conf.h"

/**
 * Generically creates a vertical buttons menu.
 * Calculates the spaces between the buttons according to their number, widths and heights.
 */
Link* create_button_menu(int height, int width, int num, char* games[],
		int (*handles[])(Control*), int widths[], int heights[]);

/**
 * Creates button menu as only panel in window -
 * removes current window content, adds the buttons menu
 * in full-screen and draws the window.
 */
int create_button_menu_window(int num, char* pics[], int (*handles[])(Control*),
		int widths[], int heights[], Control* window);

/**
 * Builds the start menu screen, including 3 buttons for selection:
 * Start Game, Load Game, Quit
 */
int show_main_menu(Control* window, int (*handles[])(Control*));

/**
 * Build game menu, according to definition of containing games
 */
int show_game_menu(Control* window, int (*handles[])(Control*));

/**
 * Build list of possible players options
 */
int show_player_select(Control* window, int (*empty)(Control*),
		int (*player)(Control*), int (*cancel)(Control*));

/**
 * Shows the screen with the selected game, according to request.
 * Includes game board, game options and general menu
 */
int show_game_arena(Control* window, Game *game, int (*handle)(Control*),
		int (*menu_handles[])(Control*), int (*difficulty_handle)(Control*));

/**
 * Build the side menu for the game window.
 */
Control* create_game_panel(int height, int width,
		int (*menu_handles[])(Control*));

/**
 * Build the board view for the current game.
 */
Control* create_board_panel(int width, int height, Game* game, int (*handle)(Control*));

/**
 * Builds panel showing current players and turn
 */
Control* create_info_panel(int width, int height, Game* game, int (*handle)(Control*));

/**
 * Choose highlight or regular according to whose current turn
 * Also, choose trophy if game is won,
 * or difficulty choice, if AI player
 */
void fill_parameters(Game* game, char** images);

/**
 * Show screen allowing user to select a game file
 * for loading \ saving, depending on request
 */
int show_files_menu(Control* window, int (*empty)(Control*),
		int (*file_han)(Control*), int (*cancel)(Control*));

/**
 * Clears current window - frees tree that window is its root
 */
void clear_window(Control* window);

#endif /* PLAYIT_GUI_H_ */
