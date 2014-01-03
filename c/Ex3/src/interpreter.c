/*
 * interpreter.c
 *
 *  Created on: Dec 17, 2013
 *      Author: shir
 */
#include <stdlib.h>

#include "interpreter.h"
#include "game.h"
#include "tree.h"

#define COMMAND_QUIT -1

void run_interpreter() {
    // int command;
    // game current_game = new_game(-1);
    // do {
    //     command = get_command();
    // }
    // while (command != COMMAND_QUIT);
}

void run_command(char *command){

}

void set_number_steps(game current_game, int steps) {
    current_game.depth = steps;
}

void suggest_move(game current_game){

}

void add_disc(game current_game, int column_num){
    current_game.current_board.make_move(current_game.current_board.cells, current_game.current_board.n, column_num, 1);
    update_tree(current_game.tree, &current_game.current_board, column_num, current_game.depth);
}

void restart_game(game *current_game){
    free(current_game->current_board.cells);
    free(current_game->tree);
    *current_game = new_game(current_game->depth);
}

void quit() {

}


