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

    if ((current_game = (game*)calloc(1, sizeof(game))) == NULL){
        perror("Error: standard function malloc has failed");
        return;
    }

    // create a new game (and check if we had an error creating it)
    if (new_game(current_game, -1) == 0) {
        return;
    }

    print_board(&(current_game->current_board));

    // first we have to get a depth, and only then we start the game
    if ((depth = get_first_depth()) == 0) {
        return;
    }
    current_game->depth = depth;

    // now we'll play the game until a quit accures (or until an error accures)
    play_game_forever(current_game);
    free(current_game);
    return;
}


/*
 * playing the game until a quit or error accures
 */
void play_game_forever(game *current_game) {
    char *command_line;
    command_t *command;
    int playing = 1;
    while (playing) {
        // get a valid command line
        if ((command_line = get_command_line()) == NULL) {
            return;
        }
        // parse command line (if command returns NULL it means we got an error)
        if ((command = parse_command_line(command_line)) == NULL) {
            return;
        }
        // only if the command is valid - we'll execute it
        if (validate_command(*command, current_game)) {
            // execute command assume that the command is valid. if it returns 0 it means an error accurd.
            if (execute_command(*command, current_game) == 0) {
                playing = 0;
            }
        }
		free(command);
    }

}

/*
 * gets a command and a game
 * returns if the command is valid, when realted to the current game
 */
int validate_command(command_t command, game *current_game){
    // steps must be non zero
    if ((command.command_code == COMMAND_CODE_SET_STEPS) && (command.arg == 0)) {
        printf(ERROR_MESSAGE_STEPS_NON_ZERO);
        return 0;
    }
    if (command.command_code == COMMAND_CODE_ADD_DISC){
        // column number in add disc command have to be between 1 and the width of the board
        if ( !( (command.arg >= 1) && (command.arg <= BOARD_WIDTH) ) ) {
            printf(ERROR_MESSAGE_COLUMN_NUMBER_NOT_VALID);
            return 0;
        }
        // column can't be full
        if (current_game->current_board.cells[0][command.arg - 1] != 0) {
            printf(ERROR_MESSAGE_COLUMN_FULL, command.arg);
            return 0;
        }
    }

    // command not found
    if (command.command_code == COMMAND_CODE_NOT_FOUND) {
        printf(ERROR_MESSAGE_COMMAND_NOT_FOUND);
        return 0;
    }

    // set_number_steps can't be more than MAX_STEPS_NUMBER
    if ((command.command_code == COMMAND_CODE_SET_STEPS) && (command.arg > MAX_STEPS_NUMBER)) {
        printf(ERROR_MESSAGE_STEPS_OVER_LIMIT);
        return 0;
    }

    // if the game is over we don't allow the commands: add_disc, suggest_move
    if (current_game->game_over) {
        if (command.command_code == COMMAND_CODE_ADD_DISC || command.command_code == COMMAND_CODE_SUGGEST_MOVE) {
            printf(ERROR_MESSAGE_GAME_OVER);
            return 0;
        }
    }

    // everything is O.K! :D
    return 1;
}

/*
 * gets a command and a game, executes the command and changing game accoringly.
 * assumes the command is valid.
 * retuns if the execution succeeded and 0 if an error has accured
 */
int execute_command(command_t command, game *current_game) {
    int preferred_move;

    // restart_game
    if (command.command_code == COMMAND_CODE_RESTART) {
        // creating new game
        if ((new_game(current_game, current_game->depth)) == 0) {
            return 0;
        }
        printf(MESSAGE_GAME_RESTARTED);
        print_board(&(current_game->current_board));
        return 1;
    }

    // quit
    if (command.command_code == COMMAND_CODE_QUIT) {
        remove_tree(current_game->tree->root);
        free(current_game->tree);
        return 0;
    }

    // set_number_steps #
    if (command.command_code == COMMAND_CODE_SET_STEPS) {
        current_game->depth = command.arg;
        return 1;
    }

    // add_disc
    if (command.command_code == COMMAND_CODE_ADD_DISC) {
        execute_move(&(current_game->current_board), BOARD_HEIGHT, command.arg - 1, 1);

        // check if the user just won
        if (won_board(current_game->current_board)) {
            // print the board, the won message, and bring the game to game over state
            print_board(&(current_game->current_board));
            printf(MESSAGE_GAME_OVER_USER_WINS);
            current_game->game_over = 1;
            return 1;
        }

        // now it's computer turn
        current_game->is_comp_turn = 1;
        // tree isn't initialized yet?
        if (current_game->tree == NULL) {
            // so create it now
            if ((current_game->tree = create_tree(&(current_game->current_board), current_game->depth)) == NULL) {
                return 0;
            }
            current_game->tree->make_move = &make_connect4_move;
            current_game->tree->scoring_func = &connect4_scoring;

        // if the tree is already initialized - then we'll update it according to the user move
        // if the tree wasn't initialized - we don't need to anything
        } else {
            update_tree(current_game->tree, &(current_game->current_board), command.arg - 1, current_game->depth);
        }

        // now we'll get the computer's next move
        if ((preferred_move = get_computer_move(current_game)) == -1) {
            return 0;
        }
        printf(MESSAGE_GAME_COMPUTER_MOVE, preferred_move + 1);
        execute_move(&(current_game->current_board), BOARD_HEIGHT, preferred_move, -1);
        print_board(&(current_game->current_board));

        // check if the computer just won
        if (won_board(current_game->current_board)) {
            printf(MESSAGE_GAME_OVER_COMP_WINS);
            current_game->game_over = 1;
            return 1;
        }
        current_game->is_comp_turn = 0;

        // if the computer didn't win - we'll update the tree
        update_tree(current_game->tree, &(current_game->current_board), preferred_move, current_game->depth);
        return 1;
    }

    // suggest_move
    if (command.command_code == COMMAND_CODE_SUGGEST_MOVE) {
        // tree isn't initalized yet?
        if (current_game->tree == NULL) {
            // so create it now
            if ((current_game->tree = create_tree(&(current_game->current_board), current_game->depth)) == NULL) {
                return 0;
            }
            current_game->tree->make_move = &make_connect4_move;
            current_game->tree->scoring_func = &connect4_scoring;
        }

        // now - get the best move
        if ((preferred_move = get_best_move_for_player(current_game)) == -1) {
            return 0;
        }
        printf(MESSAGE_GAME_SUGGESTED_MOVE, preferred_move + 1);
        return 1;
    }

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
            // maybe it is a `quit` command?
            if (strcmp(command_line, "quit\n") == 0) {
                return 0;
            }
            printf(ERROR_MESSAGE_FIRST_COMMAND_SET_NUMBER_STEPS);            
        }
        // cmd is indeed `set number of steps`
        else {
            // but now we need to see if the depth number is ok
            depth = get_depth(command_line);
            // no 0 is not acceptible
            if (depth == 0) {
                printf(ERROR_MESSAGE_STEPS_NON_ZERO);
            }
            // also more than MAX_STEPS_NUMBER is not acceptible
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

/*
 * checks if the command line has set_number_steps command in it
 */
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
 * gets the depth of the command `set_number_steps`
 * assumes that command_line is a valid command line of `set number of steps`
 */
static int get_depth(char *command_line) {
    return str_to_int(command_line, strlen(COMMAND_SET_STEPS) + 1);
}
