/*
 * game.h
 *
 *  Created on: Nov 12, 2013
 *      Author: shir
 */

#ifndef GAME_H_
#define GAME_H_

#include <stdio.h>
#include <stdlib.h>

#include "board.h"

// Holds a move to be made on the board
typedef struct Move {
	int heap_num;
	int num_of_objects;
} Move;

// Holds the current state of the game - board and turn
typedef struct Game {
	int is_comp_turn;
	Board* board;
	int turn_counter;
} Game;

/**
 * Should check validity
 */
void request_move(Move* current_move, Board* current_board);

/**
 * Checks if user's request for moving objects from heap is acceptable for the
 * current state of the board.
 */
int checkValidity(Board* current_board, int heap_num, int objects_num);

/**
 * Performs the move as requested - actually reduces the number of objects
 * in the requested heap by the requested amount.
 */
void make_move(Board* current_board, Move* requested_move);

/**
 * Prints details of the move to the user
 */
void print_move(Move *move, int is_comp_turn);

/**
 * Prints current status of the game
 */
void print_game_status(Game game);

/**
 * Prints who won the game
 */
void print_winner(Game* game);

#endif /* GAME_H_ */
