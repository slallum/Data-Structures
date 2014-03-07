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
	Control **start_screen, **start_screen_buttons;
	start_screen_buttons = (Control**) malloc(sizeof(Control*) * 3);
	start_screen_buttons[0] = create_button(10, 10, 200, 50, NEW_GAME_IMG, NULL,
			on_new_game);
	start_screen_buttons[1] = create_button(10, 70, 200, 50, LOAD_GAME_IMG,
			NULL, on_load_game);
	start_screen_buttons[2] = create_button(10, 140, 200, 50, QUIT_IMG, NULL,
			on_quit);
	start_screen = (Control**) malloc(sizeof(Control*) * 1);
	start_screen[0] = create_fs_panel(BG_IMG, window, start_screen_buttons);
	window->children = start_screen;
	window->draw(window);
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

void on_quit(Control* btn_quit) {

}
