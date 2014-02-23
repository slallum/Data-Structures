#ifndef GAME_CONSOLE_H_
#define GAME_CONSOLE_H_

/**
 * Opens the game console's main page, asking user to select:
 * New Game \ Load Game \ Quit
 *
 * Creates both main panel and game selection panel.
 */
void start_game_console();

/**
 * Triggered by user choosing the 'New Game'
 * Changes window appearance to the game selection panel
 */
void start_select_game();

void start_tic_tac_toe();

void start_connect4();

void start_reversi();

void start_game_arena();

#endif /* GAME_CONSOLE_H_ */
