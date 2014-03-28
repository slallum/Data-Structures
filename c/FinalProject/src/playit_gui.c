/*
 * playit_gui.c
 *
 *  Created on: Mar 1, 2014
 *      Author: shir
 */

#include "playit_gui.h"
#include "game_framework.h"

extern char* current_tiles[3];

Control* create_button_menu(int height, int width, int num, char* pics[],
		int (*handles[])(Control*), int widths[], int heights[]) {

	int i, total_height = 0;
	int spacing, current = MARGIN_H;
	Link *head = (Link*) calloc(1, sizeof(Link));
	Link *buttons_next = head;

	for (i = 0; i < num; i++) {
		total_height += heights[i];
	}
	spacing = ((height - current * 2 - total_height) / num) / 2;
	for (i = 0; i < num - 1; i++) {
		buttons_next->value = create_button((width - widths[i]) / 2,
				current + spacing, i, 0, widths[i], heights[i], pics[i], handles[i]);
		current += heights[i] + spacing;
		buttons_next->next = (Link*) calloc(1, sizeof(Link));
		buttons_next = buttons_next->next;
	}
	buttons_next->value = create_button((WIN_W - widths[i]) / 2,
			current + spacing, i, 0, widths[i], heights[i], pics[i], handles[i]);
	buttons_next->next = NULL;
	return create_fs_panel(BG_IMG, head);
}

int show_main_menu(Control* window) {
	char* pics[4] = { PLAYIT_IMG, NEW_GAME_IMG, LOAD_GAME_IMG, QUIT_IMG };
	int (*handles[4])(
			Control*) = {empty_select, on_new_game, on_load_game, on_select_quit };
	int widths[4] = { LOGO_DIM, BUT_W, BUT_W, BUT_W };
	int heights[4] = { LOGO_DIM, BUT_H, BUT_H, BUT_H };
	clear_window(window);
	window->children_head = (Link*) calloc(1, sizeof(Link));
	window->children_head->value = create_button_menu(
			window->height, window->width, 4, pics, handles, widths, heights);
	window->children_head->value->parent = window;
	window->children_head->next = NULL;
	return draw(window);
}

int show_game_menu(Control* window) {
	char* pics[NUM_GAMES + 2] = { SELECT_G_IMG, TIC_TAC_TOE_IMG, CONNECT4_IMG,
			REVERSI_IMG, CANCEL_IMG };
	int (*handles[NUM_GAMES + 2])(Control*) =
	{	empty_select, TIC_TAC_TOE_HAN, CONNECT4_HAN, REVERSI_HAN, CANCEL_HAN };
	int widths[NUM_GAMES + 2] = { TITLE_W, BUT_W, BUT_W, BUT_W, BUT_W };
	int heights[NUM_GAMES + 2] = { TITLE_H, BUT_H, BUT_H, BUT_H, BUT_H };
	clear_window(window);
	window->children_head = (Link*) calloc(1, sizeof(Link));
	window->children_head->value = create_button_menu(
			window->height, window->width, NUM_GAMES + 2, pics, handles, widths, heights);
	window->children_head->value->parent = window;
	window->children_head->next = NULL;
	return draw(window);
}

int show_player_select(Control* window) {
	char* pics[NUM_PLAY_TYPES + 2] = { SELECT_P_IMG, P_VS_P_IMG, P_VS_A_IMG,
			A_VS_P_IMG, A_VS_A_IMG, CANCEL_IMG };
	int (*handles[NUM_PLAY_TYPES + 2])(Control*) = {
			empty_select, P_VS_P_HAN, P_VS_A_HAN, A_VS_P_HAN, A_VS_A_HAN, CANCEL_HAN
			};
	int widths[NUM_PLAY_TYPES + 2] = { TITLE_W, BUT_W, BUT_W, BUT_W, BUT_W, BUT_W };
	int heights[NUM_PLAY_TYPES + 2] = { TITLE_H, BUT_H, BUT_H, BUT_H, BUT_H, BUT_H };
	clear_window(window);
	window->children_head = (Link*) calloc(1, sizeof(Link));
	window->children_head->value = create_button_menu(window->height, window->width,
			NUM_PLAY_TYPES + 2,  pics, handles, widths, heights);
	window->children_head->value->parent = window;
	window->children_head->next = NULL;
	return draw(window);
}

int show_game_arena(Control* window, Game *game) {

	Link *buttons_next;
	clear_window(window);
	window->children_head = (Link*) calloc(1, sizeof(Link));
	buttons_next = window->children_head;

	buttons_next->value = create_board(BOARD_PANEL_W, window->height,
			game->board.n, game->board.m, game->board.cells);
	buttons_next->next = (Link*) calloc(1, sizeof(Link));
	buttons_next = buttons_next->next;
	buttons_next->value = create_game_menu(window->height, window->width - BOARD_PANEL_W);
	buttons_next->next = NULL;

	return draw(window);
}

Control* create_game_menu(int height, int width) {
	char* pics[4] = { RESTART_GAME_IMG, SAVE_GAME_IMG, MAIN_MENU_IMG, QUIT_IMG };
	int (*handles[4])(Control*) = { on_select_restart, on_select_save, on_select_main, on_select_quit };
	int widths[4] = { BUT_W, BUT_W, BUT_W, BUT_W };
	int heights[4] = { BUT_H, BUT_H, BUT_H, BUT_H };
	return create_button_menu(height, width, 4, pics, handles, widths, heights);
}

Control* create_board(int width, int height, int n, int m, int** cells) {

	int i, j, current_x, current_y;
	Link *head = (Link*) calloc(1, sizeof(Link));
	Link *buttons_next = head;

	current_y = (height - (n * TILE_H) - ((n-1) * TILE_SPACE)) / 2;
	current_x = (width - (m * TILE_W) - ((m-1) * TILE_SPACE)) / 2;
	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++) {
			buttons_next->value = create_button(
					current_x, current_y, i, j, TILE_W, TILE_H, current_tiles[cells[i][j] % 3], on_select_tile);
			current_x += TILE_SPACE;
			current_y += TILE_SPACE;
			if ((i == n-1) && (j == m-1)) {
				buttons_next->next = NULL;
			} else {
				buttons_next->next = (Link*) calloc(1, sizeof(Link));
				buttons_next = buttons_next->next;
			}
		}
	}
	return create_panel(0, 0, 0, 0, width, height, BG_IMG, head);
}

void set_reversi_tiles() {
	current_tiles[0] = RN_IMG;
	current_tiles[1] = RW_IMG;
	current_tiles[2] = RB_IMG;
}

void set_tictactoe_tiles() {
	current_tiles[0] = TTTN_IMG;
	current_tiles[1] = TTTX_IMG;
	current_tiles[2] = TTTO_IMG;
}

void set_connect4_tiles() {
	current_tiles[0] = C4N_IMG;
	current_tiles[1] = C4P1_IMG;
	current_tiles[2] = C4P2_IMG;
}

void clear_window(Control* window) {
	if (window->children_head != NULL ) {
		free_UI_tree(window->children_head->value);
		free(window->children_head);
	}
}
