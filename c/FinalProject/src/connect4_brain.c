#include "connect4_brain.h"
#include "game_framework.h"
#include "board.h"
#include "tree.h"

Game *new_game() {
	Game game;
	game.board = new_board(BOARD_HEIGHT, BOARD_WIDTH);
	game.is_first_players_turn = 1;

	game.first_player_ai = AI_NOT_SET;
	game.second_player_ai = AI_NOT_SET;

	game.game_over = 0;

	// game.new_game = new_game;
	game.available_moves = available_moves;
	game.won_board = won_board;

	game.depth = 1;
	game.tree = create_tree(&game.board, game.depth)
	game.difficulties = {1,2,3,4,5,6,7}

	return &game;
  //   int **cells;
  //   int i;

  //   // allocate all the cells
  //   if ((cells = (int**)calloc(BOARD_HEIGHT, sizeof(int*))) == NULL) {
  //       perror("Error: standard function malloc has failed");
  //       return 0;
  //   }
  //   for (i=0; i<BOARD_HEIGHT; i++) {
  //       if ((cells[i] = (int*)calloc(BOARD_WIDTH, sizeof(int))) == NULL) {
  //           perror("Error: standard function malloc has failed");
  //           return 0;
  //       }
  //   }
  //   // create  the board
  //   board_t current_board = { cells, BOARD_HEIGHT, BOARD_WIDTH, &connect4_scoring, &make_connect4_move };

  //   current_game->current_board = current_board;
  //   current_game->is_comp_turn = 0;
  //   if (current_game->tree != NULL) {
  //   	remove_tree(current_game->tree->root);
  //   }
  //   // creating the tree
  //   // if depth not set yet - we'll create a tree with only 1 depth
  //   if (depth == DEPTH_NOT_SET) {
  //   	if ((current_game->tree = create_tree(&(current_game->current_board), 1)) == NULL) {
		// 	return 0;
		// }
  //   // depth is already set - create the the way it should be
  //   } else {
  //   	if ((current_game->tree = create_tree(&(current_game->current_board), depth)) == NULL) {
		// 	return 0;
		// }
  //   }
  //   current_game->depth=depth;
  //   current_game->game_over=0;
  //   return 1;
}

