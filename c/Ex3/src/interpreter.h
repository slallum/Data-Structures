#ifndef INTERPRETER_H_
#define INTERPRETER_H_

#include "game.h"

void run_interpreter();

void run_command(char *command);

void set_number_steps(int steps);

void suggest_move(game current_game);

void add_disc(game current_game, int column_num);

void restart_game(game current_game);

void quit();


#endif /* INTERPRETER_H_ */
