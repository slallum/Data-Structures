/*
 * playit_gui.c
 *
 *  Created on: Mar 1, 2014
 *      Author: shir
 */

#include "playit_gui.h"
#include "game_framework.h"

/**
 * Generically creates a vertical buttons menu.
 * Calculates the spaces between the buttons according to their number, widths and heights.
 */
Link* create_button_menu(int height, int width, int num, char* pics[],
		int (*handles[])(Control*), int widths[], int heights[]) {

	int i, total_height = 0;
	int spacing, current = MARGIN_H;
	Link *head = (Link*) calloc(1, sizeof(Link));
	Link *buttons_next = head;
	if (head == NULL) {
		printf("Error: Failed to create button menu\n");
		return NULL;
	}
	for (i = 0; i < num; i++) {
		total_height += heights[i];
	}
	spacing = ((height - current * 2 - total_height) / num) / 2;
	// Linking all buttons with constant spacing
	for (i = 0; i < num - 1; i++) {
		buttons_next->value = create_button((width - widths[i] - 10) / 2,
				current + spacing, i, 0, widths[i], heights[i], pics[i],
				handles[i]);
		current += heights[i] + spacing;
		buttons_next->next = (Link*) calloc(1, sizeof(Link));
		if ((buttons_next->next == NULL) || (buttons_next->value == NULL)) {
			printf("Error: Failed to create button in button menu\n");
			free_UI_children(head);
			return NULL;
		}
		buttons_next = buttons_next->next;
	}
	// Adding last link in list
	buttons_next->value = create_button((width - widths[i] - 10) / 2,
			current + spacing, i, 0, widths[i], heights[i], pics[i],
			handles[i]);
	if (buttons_next->value == NULL) {
		printf("Error: Failed to create button in button menu\n");
		free_UI_children(head);
		return NULL;
	}
	buttons_next->next = NULL;
	return head;
}

int create_button_menu_window(int num, char* pics[], int (*handles[])(Control*),
		int widths[], int heights[], Control* window) {
	Link* new_child = (Link*) calloc(1, sizeof(Link));
	if (new_child == NULL) {
		printf("Error: Failed to create new window\n");
		return 1;
	}
	new_child->value = create_fs_panel(BG_IMG,
			create_button_menu(window->height, window->width, num, pics,
					handles, widths, heights));
	if (new_child->value == NULL) {
		free(new_child);
		printf("Error: Failed to create new button menu\n");
		return 1;
	}
	new_child->value->parent = window;
	new_child->next = NULL;

	// All went well with building new window
	clear_window(window);
	window->children_head = new_child;
	if (draw(window)) {
		return flip(window);
	}
	// Already destroyed old window but could not draw new
	// Cannot continue as the UI tree elements are needed
	// UI tree is freed at exit
	return 0;
}

int show_main_menu(Control* window, int (*handles[])(Control*)) {
	char* pics[4] = { PLAYIT_IMG, NEW_GAME_IMG, LOAD_GAME_IMG, QUIT_IMG };
	int widths[4] = { LOGO_DIM, BUT_W, BUT_W, BUT_W };
	int heights[4] = { LOGO_DIM, BUT_H, BUT_H, BUT_H };
	return create_button_menu_window(4, pics, handles, widths, heights, window);
}

int show_game_menu(Control* window, int (*handles[])(Control*)) {
	char* pics[NUM_GAMES + 2] = { SELECT_G_IMG, TIC_TAC_TOE_IMG, CONNECT4_IMG,
			REVERSI_IMG, CANCEL_IMG };
	int widths[NUM_GAMES + 2] = { TITLE_W, BUT_W, BUT_W, BUT_W, BUT_W };
	int heights[NUM_GAMES + 2] = { TITLE_H, BUT_H, BUT_H, BUT_H, BUT_H };
	return create_button_menu_window(NUM_GAMES + 2, pics, handles, widths,
			heights, window);
}

int show_player_select(Control* window, int (*empty)(Control*),
		int (*player)(Control*), int (*cancel)(Control*)) {
	int i;
	char* pics[NUM_PLAY_TYPES + 2] = { SELECT_P_IMG, P_VS_P_IMG, P_VS_A_IMG,
			A_VS_P_IMG, A_VS_A_IMG, CANCEL_IMG };
	int widths[NUM_PLAY_TYPES + 2] = { TITLE_W, BUT_W, BUT_W, BUT_W, BUT_W,
			BUT_W };
	int heights[NUM_PLAY_TYPES + 2] = { TITLE_H, BUT_H, BUT_H, BUT_H, BUT_H,
			BUT_H };
	int (*handles[NUM_PLAY_TYPES + 2])(Control*) = {empty };
	for (i = 1; i <= NUM_PLAY_TYPES; i++) {
		handles[i] = player;
	}
	handles[i] = cancel;
	return create_button_menu_window(NUM_PLAY_TYPES + 2, pics, handles, widths,
			heights, window);
}

int show_game_arena(Control* window, Game *game, int (*handle)(Control*),
		int (*menu_handles[])(Control*), int (*handle_difficulty)(Control*), int button_num) {

	Control* panels[3];
	int i = 0, valid = 1;
	Link* children_head = (Link*) calloc(1, sizeof(Link));
	Link* buttons_next = children_head;
	if (children_head == NULL) {
		printf("Error: Failed to create game arena\n");
		return 1;
	}
	panels[0] = create_board_panel(BOARD_PANEL_W, BOARD_PANEL_H, game,
			handle);
	panels[1] = create_game_panel(window->height,
			window->width - (BOARD_PANEL_W), menu_handles, button_num);
	panels[2] = create_info_panel((BOARD_PANEL_W),
			window->height - (BOARD_PANEL_H), game, handle_difficulty);
	for (i = 0; i < 3; i++) {
		if (panels[i] == NULL) {
			valid = 0;
		} else if (!valid) {
			free_UI_tree(panels[i]);
		} else {
			buttons_next->value = panels[i];
			buttons_next->value->parent = window;
			if ((i < 2) && (panels[i + 1] != NULL)) {
				buttons_next->next = (Link*) calloc(1, sizeof(Link));
				if (buttons_next->next == NULL) {
					valid = 0;
				} else {
					buttons_next = buttons_next->next;
				}
			} else {
				buttons_next->next = NULL;
			}
		}
	}
	// Problem creating game arena
	if (!valid) {
		free_UI_children(children_head);
		printf("Error: Failed to create game arena\n");
		return 1;
	}
	// All went well in building new window
	clear_window(window);
	window->children_head = children_head;
	if (draw(window)) {
		return flip(window);
	}
	return 0;
}

Control* create_game_panel(int height, int width,
		int (*menu_handles[])(Control*), int button_num) {
	char* pics[5] = { RESTART_GAME_IMG, SAVE_GAME_IMG,
			MAIN_MENU_IMG, QUIT_IMG, RESUME_GAME_IMG };
	int widths[5] = { BUT_W, BUT_W, BUT_W, BUT_W, BUT_W };
	int heights[5] = { BUT_H, BUT_H, BUT_H, BUT_H, BUT_H };
	return create_panel(WIN_W - width, WIN_H - height, 0, 1, width, height,
			BG_IMG, create_button_menu(height, width, button_num, pics, menu_handles,
			widths,	heights));
}

Control* create_board_panel(int width, int height, Game* game,
		int (*handle)(Control*)) {

	int i, j, current_x, current_y, initial_x;
	Link *head = (Link*) calloc(1, sizeof(Link));
	Link *buttons_next = head;
	if (head == NULL) {
		printf("Error: Failed to create game board\n");
		return NULL;
	}

	// Calculating start spacing according to size
	// Available height\width - all tiles height\width - all tile spacings
	current_y = (height - (game->board->n * TILE_H)
			- ((game->board->n - 1) * TILE_SPACE)) / 2;
	initial_x = (width - (game->board->m * TILE_W)
			- ((game->board->m - 1) * TILE_SPACE)) / 2;
	current_x = initial_x;
	for (i = 0; i < game->board->n; i++) {
		for (j = 0; j < game->board->m; j++) {
			buttons_next->value = create_button(current_x, current_y, i, j,
					TILE_W, TILE_H,
					game->tiles[(game->board->cells[i][j] + 4) % 4], handle);
			current_x += TILE_W + TILE_SPACE;
			if ((i == game->board->n - 1) && (j == game->board->m - 1)) {
				buttons_next->next = NULL;
			} else {
				buttons_next->next = (Link*) calloc(1, sizeof(Link));
				if (buttons_next->next == NULL) {
					printf("Error: Failed to create game board\n");
					free_UI_children(head);
					return NULL;
				}
				buttons_next = buttons_next->next;
			}
		}
		current_y += TILE_H + TILE_SPACE;
		current_x = initial_x;
	}
	return create_panel(0, 0, 0, 0, width, height, BG_IMG, head);
}

Control* create_info_panel(int width, int height, Game* game,
		int (*handle)(Control*)) {

	int curr_x = INFO_PANEL_X, curr_y = INFO_PANEL_Y;
	int i, j, valid = 1;
	char* images[4];
	Control* buttons[2][2];
	Link *head = (Link*) calloc(1, sizeof(Link));
	Link* buttons_next = head;
	if (buttons_next == NULL) {
		return NULL;
	}
	fill_parameters(game, images);
	buttons[0][0] = create_label(curr_x, curr_y, 0, 0, BUT_W, BUT_H,
			images[0]);
	curr_x += BUT_W + INFO_PANEL_X;
	buttons[0][1] = create_button(curr_x, curr_y, 0, 1, TILE_W, TILE_H,
			images[2], handle);
	curr_x = INFO_PANEL_X;
	curr_y += BUT_H + INFO_PANEL_Y;
	buttons[1][0] = create_label(curr_x, curr_y, 1, 0, TILE_W, TILE_H,
			images[1]);
	curr_x += INFO_PANEL_X + BUT_W;
	buttons[1][1] = create_button(curr_x, curr_y, 1, 1, TILE_W, TILE_H,
			images[3], handle);

	for (i = 0; i < 2; i++) {
		for (j = 0; j < 2; j++) {
			if (buttons[i][j] == NULL) {
				valid = 0;
			} else if (!valid) {
				free_UI_tree(buttons[i][j]);
			} else {
				buttons_next->value = buttons[i][j];
				if ((i != 1) || (j != 1)) {
					buttons_next->next = (Link*) calloc(1, sizeof(Link));
					if (buttons_next->next == NULL) {
						valid = 0;
					} else {
						buttons_next = buttons_next->next;
					}
				} else {
					buttons_next->next = NULL;
				}
			}
		}
	}
	// Cannot build panel due to problem with buttons
	if (!valid) {
		free_UI_children(head);
		return NULL;
	}
	// All went well with children buttons
	return create_panel(0, BOARD_PANEL_H, 1, 0, width, height, BG_IMG, head);
}

/**
 * Choose highlight or regular according to whose current turn
 * Also, choose trophy if game is won,
 * or difficulty choice, if AI player
 */
void fill_parameters(Game* game, char** images) {

	images[2] = NO_IMG;
	images[3] = NO_IMG;
	if (game->current_player == 0 && game->game_over) {
		both_crown(images);
	}
	if (game->current_player == FIRST_PL_TURN) {
		first_crown(images, game);
	} else {
		second_crown(images, game);
	}
	if (!game->game_over) {
		if (game->first_player_ai == AI_PLAYING) {
			add_difficulty(images, 2, game->first_player_depth);
		}
		if (game->second_player_ai == AI_PLAYING) {
			add_difficulty(images, 3, game->second_player_depth);
		}
	}
}

void first_crown(char** images, Game* game) {
	images[0] = PLAYER1_H_IMG;
	images[1] = PLAYER2_IMG;
	if (game->game_over) {
		images[2] = TROPHY_IMG;
	}
}

void second_crown(char** images, Game* game) {
	images[0] = PLAYER1_IMG;
	images[1] = PLAYER2_H_IMG;
	if (game->game_over) {
		images[3] = TROPHY_IMG;
	}
}

void both_crown(char** images) {
	images[0] = PLAYER1_H_IMG;
	images[1] = PLAYER2_H_IMG;
	images[2] = TROPHY_IMG;
	images[3] = TROPHY_IMG;
}

void add_difficulty(char** images, int cell, int depth) {
	images[cell] = (char*) malloc(sizeof(char) * 2);
	if ((images[cell] == NULL) || (sprintf(images[cell], "%d", depth) <= 0)) {
		images[cell] = NO_IMG;
	}
}

int show_files_menu(Control* window, int (*empty)(Control*),
		int (*file_han)(Control*), int (*cancel)(Control*), int* exist) {

	int i;
	char* pics[FILES_NUM + 2] = { FILE_SELECT };
	int widths[FILES_NUM + 2] = { TITLE_W };
	int heights[FILES_NUM + 2] = { TITLE_H };
	int (*handles[FILES_NUM + 2])(Control*) = {empty };
	// According to number of files,
	// add names, sizes and functions to structs.
	// Giving a name to a button, as oppose to a valid path
	// will create it on the fly using text
	for (i = 1; i <= FILES_NUM; i++) {
		if (exist[i - 1]) {
			pics[i] = (char*) malloc(strlen(FILE_NAME) + sizeof(char) * 4 + 1);
			sprintf(pics[i], "\"%s %d\"", FILE_NAME, i);
		} else {
			pics[i] = (char*) malloc(strlen(FILE_NAME) + sizeof(char) * 2 + 1);
			sprintf(pics[i], "%s %d", FILE_NAME, i);
		}
		widths[i] = TEXT_W;
		heights[i] = TEXT_H;
		handles[i] = file_han;
	}
	pics[i] = CANCEL_IMG;
	widths[i] = BUT_W;
	heights[i] = BUT_H;
	handles[i] = cancel;
	return create_button_menu_window(FILES_NUM + 2, pics, handles, widths,
			heights, window);
}

void clear_window(Control* window) {
	if (window->children_head != NULL ) {
		free_UI_tree(window->children_head->value);
		free(window->children_head);
	}
}
