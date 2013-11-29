#ifndef AI_NIM_H_
#define AI_NIM_H_

#include "board.h"
#include "game.h"


Move calculate_next_best_move(Board current_board);

static int calculate_nim_sum(Board board);

#endif /* AI_NIM_H_ */