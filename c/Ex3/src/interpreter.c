/*
 * interpreter.c
 *
 *  Created on: Dec 17, 2013
 *      Author: shir
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "io.h"
#include "interpreter.h"
#include "game.h"
#include "tree.h"
#include "board.h"

static int get_depth(char *command_line);
static int is_set_depth_command(char* command_line);

void run_interpreter() {
    int depth;
    game *current_game;

    current_game = new_game(-1);
    if (current_game == NULL) {
        return;
    }

    print_board(&(current_game->current_board));

    depth = get_first_depth();
    // error
    if (depth == 0) {
        return;
    }
    current_game->depth = depth;
    
    play_game_forever(current_game);
    return;
}


void play_game_forever(game *current_game) {
    char *command_line;
    command_t *command;
    while (1) {
        if ((command_line = get_command_line()) == NULL) {
            return;
        }

        if ((command = parse_command_line(command_line)) == NULL) {
            return;
        }
        if (validate_command(*command, current_game)) {
            if (execute_command(*command, current_game) == 0) {
                return;
            }
        }
    }

}

int validate_command(command_t command, game *current_game){
    // TODO: implement
    return 0;
}
int execute_command(command_t command, game *current_game) {
    // TODO: implement
    return 0;    
}


/*
/ gets the depth from the first command
/ keeps running until an error is accured or we got a good depth (between 1 and MAX_STEPS_NUMBER)
*/
int get_first_depth() {
    char *command_line;
    int depth = -1;

    while (1) {
        command_line = get_command_line();
        // error in get_command_line - exit
        if (command_line == NULL) {
            return 0;
        }
        // got cmd - checking that the first command line is `set number of steps`
        if (!is_set_depth_command(command_line)) {
            printf(ERROR_MESSAGE_FIRST_COMMAND_SET_NUMBER_STEPS);            
        }
        // cmd is indeed `set number of steps`
        else {
            depth = get_depth(command_line);
            if (depth == 0) {
                printf(ERROR_MESSAGE_STEPS_NON_ZERO);
            }
            else if (depth > MAX_STEPS_NUMBER) {
                printf(ERROR_MESSAGE_STEPS_OVER_LIMIT);
            }
            // alright - the depth if ok!
            else {
                return depth;
            }
        }
    }
        
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
    current_game = new_game(current_game->depth);
}

void quit() {

}


static int is_set_depth_command(char* command_line) {
    int i;
    for (i=0; i<strlen(COMMAND_SET_STEPS); i++){
        if (command_line[i] != COMMAND_SET_STEPS[i]) {
            return 0;
        }
    }
    // we assume the user gives us a good parameter after the command
    return 1;
}


/* 
* assumes that command_line is a valid command line of `set number of steps`
*/
static int get_depth(char *command_line) {
    return str_to_int(command_line, strlen(COMMAND_SET_STEPS) + 1);
}