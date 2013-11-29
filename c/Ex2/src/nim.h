/*
 * nim.h
 *
 *  Created on: Nov 12, 2013
 *      Author: shir
 */

#ifndef NIM_H_
#define NIM_H_

#include "game.h"
#include "board.h"

int main(void);

void calculate_next_best_move(Move* current_move, Board* current_board);

void play_game();

#endif /* NIM_H_ */
