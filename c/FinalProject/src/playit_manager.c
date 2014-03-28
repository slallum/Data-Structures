/*
 * playit_manager.c
 *
 *  Created on: Mar 13, 2014
 *      Author: shir
 */

#include "playit_manager.h"

extern Game *game;

int on_new_game(Control* btn_new_game) {

	return !show_game_menu(get_root(btn_new_game));
}

int on_load_game(Control* btn_load_game) {
	return 0;
}

int on_select_quit(Control* btn_quit) {
	return 1;
}

int on_select_tictactoe(Control* btn_game) {
	// TODO create game!
	set_tictactoe_tiles();
	return !show_player_select(get_root(btn_game));
}

int on_select_reversi(Control* btn_game) {
	// TODO create game!
	set_reversi_tiles();
	return !show_player_select(get_root(btn_game));
}

int on_select_connect4(Control* btn_game) {
	// TODO create game!
	set_connect4_tiles();
	return !show_player_select(get_root(btn_game));
}

int on_cancel(Control* btn) {

	return !show_main_menu(get_root(btn));
}

int on_select_pl_pl(Control* btn_pl_type) {
	//TODO
//	game->first_player_ai = 0;
//	game->second_player_ai = 0;
	return !show_game_arena(get_root(btn_pl_type));
}

int on_select_pl_ai(Control* btn_pl_type) {
	//TODO
//	game->first_player_ai = 0;
//	game->second_player_ai = 1;
	return !show_game_arena(get_root(btn_pl_type));
}

int on_select_ai_ai(Control* btn_pl_type) {
//	game->first_player_ai = 1;
//	game->second_player_ai = 1;
	return !show_game_arena(get_root(btn_pl_type));
}

int on_select_ai_pl(Control* btn_pl_type) {
	//TODO
//	game->first_player_ai = 1;
//	game->second_player_ai = 0;
	return !show_game_arena(get_root(btn_pl_type), game);
}

int on_select_tile(Control* btn_tile) {
	//TODO make a move in game!
	//TODO recreate board or just change specific tile?
	return 0;
}

int on_select_restart(Control* btn) {
	//TODO empty board
	//TODO make current player the first
	//TODO recreate board
	return 0;
}

int on_select_save(Control* btn) {
	//TODO save game
	return 0;
}

int on_select_main(Control* btn) {
	return !show_main_menu(get_root(btn));
}

Control* get_root(Control* control) {
	while (control->parent != NULL) {
		control = control->parent;
	}
	return control;
}
