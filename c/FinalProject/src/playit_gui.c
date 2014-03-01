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

	Control* start_screen_buttons[3] = { create_button(10, 10, 200, 50,
			"../resources/NewGame.png", NULL, on_new_game), create_button(10,
			70, 200, 50, "../resources/LoadGame.png", NULL, on_load_game),
			create_button(10, 140, 200, 50, "../resources/Quit.png", NULL,
					on_quit) };
	Control* start_screen[1] = { create_fs_panel(window,
			"../resources/Background.png", window, start_screen_buttons) };
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
