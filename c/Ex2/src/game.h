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

typedef struct Move {
	int heap_num;
	int num_of_objects;
} Move;

typedef struct Game {
	int is_comp_turn;
	Board* board;
	int turn_counter;
} Game;

/**
 * Should check validity
 */
void request_move(Move* current_move, Board* current_board);

int checkValidity(Board* current_board, int heap_num, int objects_num);

void make_move(Board* current_board, Move* requested_move);

void print_move(Move *move, int is_comp_turn);

void print_game_status(Game* game);

void print_winner(Game* game);

#endif /* GAME_H_ */
