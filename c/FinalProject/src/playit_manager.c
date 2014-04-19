/*
 * playit_manager.c
 *
 *  Created on: Mar 13, 2014
 *      Author: shir
 */

#include "playit_manager.h"

// Global object holding current game being played
Game* game = NULL;

// Handles for creating game side menu
int (*game_menu_handles[5])(Control*) = { on_select_restart, on_select_save,
		on_cancel, on_select_quit, on_select_resume };

/**
 * Handle button 'New Game' click.
 * Moves to game selection screen.
 *
 * @param	The button object
 */
int on_new_game(Control* btn_new_game) {
	int (*handles[NUM_GAMES + 2])(Control*) =
	{	empty_select, TIC_TAC_TOE_HAN, CONNECT4_HAN, REVERSI_HAN, CANCEL_HAN };
	return !show_game_menu(get_root(btn_new_game), handles);
}

/**
 * Handle button 'Load Game' click.
 * Moves to file selection screen.
 */
int on_load_game(Control* btn_load_game) {

	int exist[FILES_NUM], i;
	for (i = 1; i <= FILES_NUM; i++) {
		exist[i - 1] = file_exists(i);
	}
	return !show_files_menu(get_root(btn_load_game), empty_select,
			on_select_load_file, on_cancel, exist);
}

/**
 * Handle button 'Quit'.
 * Closes window.
 */
int on_select_quit(Control* btn_quit) {
	if (game != NULL) {
		free_game(game);
	}
	return 1;
}

/**
 * Handles choice of a ttt game.
 * Moves to selecting type of players.
 */
int on_select_tictactoe(Control* btn_game) {
	game = ttt_new_game();
	return !show_player_select(get_root(btn_game), empty_select,
			on_select_player, on_cancel);
}

/**
 * Handles choice of reversi game.
 * Moves to selecting type of players.
 */
int on_select_reversi(Control* btn_game) {
	game = reversi_new_game();
	return !show_player_select(get_root(btn_game), empty_select,
			on_select_player, on_cancel);
}

/**
 * Handles choice of connect4 game.
 * Moves to selecting type of players.
 */
int on_select_connect4(Control* btn_game) {
	game = connect4_new_game();
	return !show_player_select(get_root(btn_game), empty_select,
			on_select_player, on_cancel);
}

/**
 * Returns to main menu without creating game.
 */
int on_cancel(Control* btn) {
	int (*handles[4])(Control*) = {
		empty_select, on_new_game, on_load_game, on_select_quit };
	if (game != NULL) {
		free_game(game);
	}
	return !show_main_menu(get_root(btn), handles);
}

/**
 * According to i of the selected button,
 * updates the current player.
 * Note: Counts on the order of the players.
 *       New types can be added easily as long as in the end..
 */
int on_select_player(Control* btn_pl_type) {

	if ((btn_pl_type->i == 2) || (btn_pl_type->i == 4)) {
		game->second_player_ai = AI_PLAYING;
	} else {
		game->second_player_ai = PL_PLAYING;
	}
	if ((btn_pl_type->i == 3) || (btn_pl_type->i == 4)) {
		game->first_player_ai = AI_PLAYING;
	} else {
		game->first_player_ai = PL_PLAYING;
	}
	return show_arena(get_root(btn_pl_type));
}

/**
 * When first player is AI, game arena starts paused
 * (first move is not made)
 * until clicking 'Resume'.
 * This is in order to allow setting difficulty
 */
int on_select_resume(Control* btn_tile) {
	return on_select_tile(get_root(btn_tile));
}

/**
 * Handles selection of a tile on the board.
 * Performs corresponding move according to stated by
 * current game rules.
 */
int on_select_tile(Control* btn_tile) {
	Control* current;
	int rc = handle_move(game, btn_tile->i, btn_tile->j);
	if (game->won_game(game)) {
		return !show_game_arena(get_root(btn_tile), game, empty_select,
				game_menu_handles, on_select_difficulty, 4);
	}
	if ((rc == 0) && switch_player(game)) {
		current = get_root(btn_tile);
		if (show_game_arena(current, game, empty_select,
				game_menu_handles, on_select_difficulty, 4)) {
			return on_select_tile(current);
		}
	}
	return !show_game_arena(get_root(btn_tile), game, on_select_tile,
			game_menu_handles, on_select_difficulty, 4);
}

/**
 * Start new game with exact same parameters as current.
 */
int on_select_restart(Control* btn) {
	restart_game(game);
	return show_arena(get_root(btn));
}

/**
 * Save current game state to a file, without stopping the game.
 */
int on_select_save(Control* btn) {

	int exist[FILES_NUM], i;
	for (i = 1; i <= FILES_NUM; i++) {
		exist[i - 1] = file_exists(i);
	}
	return !show_files_menu(get_root(btn),
			empty_select, on_select_save_file, on_cancel, exist);
}

/**
 * Handles save of current game to selected file,
 * denoted by the i of the given file_btn
 */
int on_select_save_file(Control* file_btn) {
	if (!save_game(file_btn->i, game)) {
		// TODO error dialog?
	}
	return !show_game_arena(get_root(file_btn), game, on_select_tile,
			game_menu_handles, on_select_difficulty, 4);
}

/**
 * Handles save of current game to selected file,
 * denoted by the i of the given file_btn
 */
int on_select_load_file(Control* file_btn) {
	game = load_game(file_btn->i);
	if (game == NULL ) {
		//TODO no saved game - error dialog?
		return 0;
	}
	return !show_player_select(get_root(file_btn), empty_select,
			on_select_player, on_cancel);
}

/**
 * Clicking difficulty from menu, sets stated value as current difficulty
 * for the corresponding player (according to btn position)
 */
int on_select_difficulty(Control* btn) {
	if (btn->i == 0) {
		next_level(&(game->first_player_depth), game->depth_range);
	}
	if (btn->i == 1) {
		next_level(&(game->second_player_depth), game->depth_range);
	}
	return show_arena(get_root(btn));
}

/* --- Inner methods --- */

/**
 * Increases the player's depth by 1, mod max.
 * Also, adds 1 because not zero-indexed
 *
 * @param curr	Address of player's game depth to increase
 * @param range	Min and max depth possible as set for the current game
 */
void next_level(int* curr, int range[]) {
	*curr = (*curr + 1);
	if (*curr == range[1] + 1) {
		*curr = range[0];
	}
}

/**
 * Climb to the root of the tree
 */
Control* get_root(Control* control) {
	Control* current = control;
	while (current->parent != NULL ) {
		current = current->parent;
	}
	return current;
}

/**
 * Frees all memory allocated for the game object
 */
void free_game(Game* game) {
	free_board(game->board);
	remove_tree(game->tree->root);
}

/**
 * Opens game screen for beginning of the game.
 * If first player is AI, opens it paused,
 * with a 'Resume' button.
 * This is in order to give the opportunity to change difficulty
 */
int show_arena(Control* window) {
	if (!game->game_over && game->first_player_ai == AI_PLAYING) {
		return !show_game_arena(window, game, empty_select,
				game_menu_handles, on_select_difficulty, 5);
	} else if (game->game_over) {
		return !show_game_arena(window, game, empty_select,
				game_menu_handles, on_select_difficulty, 4);
	} else {
		return !show_game_arena(window, game, on_select_tile,
				game_menu_handles, on_select_difficulty, 4);
	}
}
