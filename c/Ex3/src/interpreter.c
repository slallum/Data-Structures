/*
 * interpreter.c
 *
 *  Created on: Dec 17, 2013
 *      Author: shir
 */

#include "interpreter.h"

void run_interpreter() {

}


void run_interpreter();

void run_command(char *command);

void set_number_steps(game current_game, int steps) {
    current_game.depth = steps;
}

void suggest_move(game current_game);

void add_disc(game current_game, int column_num);

void restart_game(game current_game);

void quit();


