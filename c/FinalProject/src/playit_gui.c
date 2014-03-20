/*
 * playit_gui.c
 *
 *  Created on: Mar 1, 2014
 *      Author: shir
 */

#include "playit_gui.h"

/**
 * Builds the start menu screen, including 3 buttons for selection:
 * Start Game, Load Game, Quit
 */
int show_main_menu(Control* window) {
	Link* label = (Link*) malloc(sizeof(Link));
	Link* button1 = (Link*) malloc(sizeof(Link));
	Link* button2 = (Link*) malloc(sizeof(Link));
	Link* button3 = (Link*) malloc(sizeof(Link));
	window->children_head = (Link*) malloc(sizeof(Link));

	label->value = create_label((WIN_W - LOGO_DIM) / 2, 30, LOGO_DIM, LOGO_DIM,
			PLAYIT_IMG);
	button1->value = create_button((WIN_W - BUT_W) / 2, 180, BUT_W, BUT_H, NEW_GAME_IMG,
			on_new_game);
	button2->value = create_button((WIN_W - BUT_W) / 2, 250, BUT_W, BUT_H, LOAD_GAME_IMG,
			on_load_game);
	button3->value = create_button((WIN_W - BUT_W) / 2, 320, BUT_W, BUT_H, QUIT_IMG, on_quit);

	label->next = button1;
	button1->next = button2;
	button2->next = button3;
	button3->next = NULL;

	window->children_head->value = create_fs_panel(BG_IMG, label);
	window->children_head->value->parent = window;
	window->children_head->next = NULL;

	return draw(window);
}

int show_game_menu(Control* window) {
	char* games[NUM_GAMES] = { TIC_TAC_TOE_IMG, CONNECT4_IMG, REVERSI_IMG };
	int (*handles[NUM_GAMES])(Control*) = { TIC_TAC_TOE_HAN, CONNECT4_HAN, REVERSI_HAN };
	int i, current, spacing;
	Link *buttons_next;
	Link *label = (Link*) malloc(sizeof(Link));

	label->value = create_label((WIN_W - TITLE_W) / 2, MARGIN_H, TITLE_W,
			TITLE_H, SELECT_G_IMG);
	label->next = (Link*) malloc(sizeof(Link));
	buttons_next = label->next;
	current = MARGIN_H + TITLE_H;
	spacing = ((window->height - current - MARGIN_H - BUT_H * NUM_GAMES)
			/ NUM_GAMES) / 2;
	for (i = 0; i < NUM_GAMES; i++) {
		buttons_next->value = create_button((WIN_W - BUT_W) / 2,
				current + spacing, BUT_W, BUT_H, games[i], handles[i]);
		current += BUT_H + spacing;
		buttons_next->next = (Link*) malloc(sizeof(Link));
		buttons_next = buttons_next->next;
	}
	buttons_next->value = create_button((WIN_W - BUT_W) / 2, current + spacing,
			BUT_W, BUT_H, CANCEL_IMG, on_cancel);
	buttons_next->next = NULL;
	if (window->children_head != NULL) {
		free_UI_tree(window->children_head->value);
		free(window->children_head);
	}
	window->children_head = NULL;
	window->children_head = (Link*) malloc(sizeof(Link));
	window->children_head->value = create_fs_panel(BG_IMG, label);
	window->children_head->value->parent = window;
	window->children_head->next = NULL;
	return draw(window);
}
