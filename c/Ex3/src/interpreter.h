#ifndef INTERPRETER_H_
#define INTERPRETER_H_

#include "game.h"
#include "io.h"


#define MAX_STEPS_NUMBER 7


int get_first_depth();
void play_game_forever(game *current_game);
int validate_command(command_t command, game *current_game);
int execute_command(command_t command, game *current_game);


void run_interpreter();

void run_command(char *command);

void set_number_steps(game current_game, int steps);

void suggest_move(game current_game);

void add_disc(game current_game, int column_num);

void restart_game(game *current_game);

void quit();


#endif /* INTERPRETER_H_ */
