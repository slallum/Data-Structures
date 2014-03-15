/*
 * playit_brain.h
 *
 *  Created on: Mar 13, 2014
 *      Author: shir
 */

#ifndef PLAYIT_BRAIN_H_
#define PLAYIT_BRAIN_H_

#include "playit_manager.h"
#include "board.h"
#include "tree.h"

typedef struct game_s {
    Board board;

    int is_first_players_turn;
    int first_player_ai;
    int second_player_ai;
    int game_over;

    int depth;
    minmax_tree *tree;
    int difficulties[];
} Game;


typedef struct game_rules_s {
	int (*available_moves)(Game*);
	int (*won_board)(Game*);
	Game (*new_game)();
} GameRules;

void start_new_game();

#endif /* PLAYIT_BRAIN_H_ */
