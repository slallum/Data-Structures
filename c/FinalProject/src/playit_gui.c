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
int show_start_screen(Control* window) {
	Link* start_screen = (Link*) malloc(sizeof(Link));
	Link* buttons_head = (Link*) malloc(sizeof(Link));
	Link* buttons_next = (Link*) malloc(sizeof(Link));

	buttons_head->value = create_button(220, 180, 200, 50, NEW_GAME_IMG,
			on_new_game);
	buttons_head->next = NULL;
	buttons_next->value = create_button(220, 250, 200, 50, LOAD_GAME_IMG,
			on_load_game);
	buttons_head->next = buttons_next;
	buttons_next->next = (Link*) malloc(sizeof(Link));
	buttons_next = buttons_next->next;
	buttons_next->value = create_button(220, 320, 200, 50, QUIT_IMG, on_quit);
	buttons_next->next = NULL;

	start_screen->value = create_fs_panel(BG_IMG, buttons_head);
	start_screen->next = NULL;
	window->children_head = start_screen;
	if (!window->draw(window, NULL )) {
		printf("Error: Failed to draw start screen\n");
		return 0;
	}
	if (SDL_Flip(window->view) != 0) {
		printf("Error: Failed to flip buffer: %s\n", SDL_GetError());
		return 0;
	}
	return 1;
}

void on_new_game(Control* btn_new_game) {

}

void on_load_game(Control* btn_load_game) {

}
