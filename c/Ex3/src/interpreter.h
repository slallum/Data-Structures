#ifndef INTERPRETER_H_
#define INTERPRETER_H_

#include "game.h"
#include "io.h"

#define MAX_STEPS_NUMBER 7

void run_interpreter();

int get_first_depth();
void play_game_forever(game *current_game);

int validate_command(command_t command, game *current_game);
int execute_command(command_t command, game *current_game);

#endif /* INTERPRETER_H_ */
