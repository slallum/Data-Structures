/*
 * playit_gui.h
 *
 *  Created on: Mar 1, 2014
 *      Author: shir
 */

#ifndef PLAYIT_GUI_H_
#define PLAYIT_GUI_H_

#include <stdio.h>
#include "gui_framework.h"

/**
 * Builds the start menu screen, including 3 buttons for selection:
 * Start Game, Load Game, Quit
 */
int show_start_screen(Control* window);

void on_new_game(Control* btn_new_game);

void on_load_game(Control* btn_load_game);

void on_quit(Control* btn_quit);

#endif /* PLAYIT_GUI_H_ */
