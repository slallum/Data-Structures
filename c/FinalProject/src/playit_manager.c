/*
 * playit_manager.c
 *
 *  Created on: Mar 13, 2014
 *      Author: shir
 */

#include "playit_manager.h"

Game* game;
char* save_game_name;

int (*game_menu_handles[4])(
		Control*) = {on_select_restart, on_select_save, on_cancel, on_select_quit
		};

int on_new_game(Control* btn_new_game) {
	int (*handles[NUM_GAMES + 2])(Control*) =
	{	empty_select, TIC_TAC_TOE_HAN, CONNECT4_HAN, REVERSI_HAN, CANCEL_HAN };
	return !show_game_menu(get_root(btn_new_game), handles);
}

int on_load_game(Control* btn_load_game) {
	return !show_files_menu(get_root(btn_load_game), empty_select,
			on_select_load_file, on_cancel);
}

int on_select_quit(Control* btn_quit) {
	return 1;
}

int on_select_tictactoe(Control* btn_game) {
	save_game_name = TTT_NAME;
	// TODO create correct game!
	game = connect4_new_game();
	return !show_player_select(get_root(btn_game), empty_select,
			on_select_player, on_cancel);
}

int on_select_reversi(Control* btn_game) {
	save_game_name = REVERSI_NAME;
	// TODO create correct game!
	game = connect4_new_game();
	return !show_player_select(get_root(btn_game), empty_select,
			on_select_player, on_cancel);
}

int on_select_connect4(Control* btn_game) {
	save_game_name = CONNECT4_NAME;
	game = connect4_new_game();
	return !show_player_select(get_root(btn_game), empty_select,
			on_select_player, on_cancel);
}

int on_cancel(Control* btn) {
	int (*handles[4])(Control*) = {
		empty_select, on_new_game, on_load_game, on_select_quit };
	return !show_main_menu(get_root(btn), handles);
}

int on_select_player(Control* btn_pl_type) {

	if ((btn_pl_type->i == 3) || (btn_pl_type->i == 4)) {
		game->first_player_ai = AI_PLAYING;
	} else {
		game->first_player_ai = PL_PLAYING;
	}
	if ((btn_pl_type->i == 2) || (btn_pl_type->i == 4)) {
		game->second_player_ai = AI_PLAYING;
	} else {
		game->second_player_ai = PL_PLAYING;
	}
	return !show_game_arena(get_root(btn_pl_type), game, on_select_tile,
			game_menu_handles, on_conf_difficulty);
}

int on_select_tile(Control* btn_tile) {
	//TODO check first if AI or regular
	// Or should make move do it all?
	int rc = handle_move(game, btn_tile->i, btn_tile->j);
	if (game->won_board(game->board)) {
		// TODO update info panel
		return !show_game_arena(get_root(btn_tile), game, empty_select,
				game_menu_handles, on_conf_difficulty);
	}
	if ((rc == 0) && switch_player(game)) {
		on_select_tile(btn_tile);
	}
	return !show_game_arena(get_root(btn_tile), game, on_select_tile,
			game_menu_handles, on_conf_difficulty);
}

int on_select_restart(Control* btn) {

	game->board = new_board(game->board->n, game->board->m);
	game->is_first_players_turn = FIRST_PL_TURN;
	return !show_game_arena(get_root(btn), game, on_select_tile,
			game_menu_handles, on_conf_difficulty);
}

int on_select_save(Control* btn) {

	return !show_files_menu(get_root(btn), empty_select, on_select_save_file,
			on_select_save_file);
}

int on_select_save_file(Control* file_btn) {
	if (!save_game(file_btn->i, game, save_game_name)) {
		// TODO error dialog?
	}
	return !show_game_arena(get_root(file_btn), game, on_select_tile,
			game_menu_handles, on_conf_difficulty);
}

int on_select_load_file(Control* file_btn) {
	game = load_game(file_btn->i);
	if (game == NULL ) {
		//TODO no saved game - error dialog?
		return 0;
	}
	return !show_player_select(get_root(file_btn), empty_select,
			on_select_player, on_cancel);
}

int on_conf_difficulty(Control* btn) {
	return !open_difficulty(game, btn, on_select_difficulty);
}

int on_select_difficulty(Control* btn) {
	if (btn->parent->j == 0) {
		game->first_player_depth = btn->j;
	}
	if (btn->parent->j == 1) {
		game->second_player_depth = btn->j;
	}
	return !show_game_arena(get_root(btn), game, on_select_tile,
			game_menu_handles, on_conf_difficulty);
}

Control* get_root(Control* control) {
	while (control->parent != NULL ) {
		control = control->parent;
	}
	return control;
}
