#ifndef CONNECT4_BRAIN_H_
#define CONNECT4_BRAIN_H_

#include "game_framework.h"

#define BOARD_HEIGHT 6
#define BOARD_WIDTH 7

Game *connect4_new_game();

int** available_moves(Game* game);
int make_move(int**, int, int, int);
int won_board(Game* game);
int get_score(int**, int, int);



#endif /* CONNECT4_BRAIN_H_ */