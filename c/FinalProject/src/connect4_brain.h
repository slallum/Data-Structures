#ifndef CONNECT4_BRAIN_H_
#define CONNECT4_BRAIN_H_

#include "game_framework.h"

#define BOARD_HEIGHT 6
#define BOARD_WIDTH 7

Game *new_game();

int** available_moves(Game game);

int won_board(Game game);

#endif /* CONNECT4_BRAIN_H_ */