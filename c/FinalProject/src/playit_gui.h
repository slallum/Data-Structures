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
#include "playit_conf.h"
#include "playit_manager.h"

/**
 * Builds the start menu screen, including 3 buttons for selection:
 * Start Game, Load Game, Quit
 */
int show_main_menu(Control* window);

/**
 * Build game menu, according to definition of containing games
 */
int show_game_menu(Control* window);

#endif /* PLAYIT_GUI_H_ */
