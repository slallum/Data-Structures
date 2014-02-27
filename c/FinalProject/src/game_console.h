#ifndef GAME_CONSOLE_H_
#define GAME_CONSOLE_H_

#include "gui_framework.h"


/**
 * Opens the game console's main page, asking user to select:
 * New Game \ Load Game \ Quit
 *
 * Creates both main panel and game selection panel.
 */
void start_game_console();

/**
 * Go over all tree and find which control is ranged around the clicked spot
 */
Control* find_clicked(int x, int y, Control* root);

#endif /* GAME_CONSOLE_H_ */
