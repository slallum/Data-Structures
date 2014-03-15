/*
 * playit_manager.c
 *
 *  Created on: Mar 13, 2014
 *      Author: shir
 */

#include "playit_manager.h"

int on_new_game(Control* btn_new_game) {

	while (btn_new_game->parent != NULL) {
		btn_new_game = btn_new_game->parent;
	}
	return !show_game_menu(btn_new_game);
}

int on_load_game(Control* btn_load_game) {
	return 0;
}

int on_quit(Control* btn_quit) {
	return 1;
}

int on_select_tictactoe(Control* btn_game) {
	return 0;
}

int on_select_reversi(Control* btn_game) {
	return 0;
}

int on_select_connect4(Control* btn_game) {
	return 0;
}

int on_cancel(Control* btn) {
	while (btn->parent != NULL) {
			btn = btn->parent;
		}
	return !show_main_menu(btn);
}
