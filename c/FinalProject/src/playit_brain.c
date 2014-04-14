/*
 * playit_brain.c
 *
 *  Created on: Mar 13, 2014
 *      Author: shir
 */

#include "playit_brain.h"

/**
 * Switches players from current to other (flips marks)
 * If currently playing is an AI player, returns 1,
 * indicating to continue fictive clicking, without waiting for user.
 */
int switch_player(Game* game) {
	if (no_moves(game, game->current_player * SECOND_PL_TURN) == 0) {
		game->current_player = game->current_player * (SECOND_PL_TURN);
	}
	if ((game->current_player == FIRST_PL_TURN) && (game->first_player_ai == AI_PLAYING)) {
		return 1;
	}
	if ((game->current_player == SECOND_PL_TURN) && (game->second_player_ai == AI_PLAYING)) {
		return 1;
	}
	return 0;
}

/**
 * Tries all moves on the board for given player,
 * until meeting one that is possible.
 * Erases each move been made.
 */
int no_moves(Game* game, int player) {

	int i = 0, j = 0, k, l;
	int avail_move = -1;
	Move* curr_move = (Move*) malloc(sizeof(Move));
	Board* temp_board = new_board(game->board->n, game->board->m);

	while ((avail_move == -1) && i < game->board->n) {
		while ((avail_move == -1) && j < game->board->m) {
			curr_move->i = i;
			curr_move->j = j;
			if (game->board->cells[i][j] == 0) {
				for (k = 0; k < game->board->n; k++) {
					// Updating temp board with real state
					for (l = 0; l < game->board->m; l++) {
						temp_board->cells[k][l]= game->board->cells[k][l];
					}
				}
				// Attempt move
				avail_move = game->make_move(temp_board, curr_move, player);
			}
			j++;
		}
		j = 0;
		i++;
	}
	free(curr_move);
	free(temp_board);
	return avail_move;
}

// TODO
/**
 * Handles all logic around making a move in the game.
 * Updates the tree for all players and get
 *
 * @return	 0 - All went well, move was made and turn should pass on
 * 			-1 - Move was not made and turn should not pass (was illegal for player)
 * 			 1 - Move was made but current player is AI, so no waiting for user
 *
 */
int handle_move(Game* game, int i, int j) {
	Move* new_move;
	if ((new_move = (Move*) malloc(sizeof(Move))) == NULL) {
		printf("Error in allocating memory for new move in handle_move.\n");
		return 0;
	}

	// get the new move
	// if we know that the current player is AI, we'll get the best move for it with minmax
	if (current_player_is_ai(game)) {
		new_move = get_best_move(game);
	// if it's a human player's turn - then i, j are the real move.
	} else {
		new_move->i = i;
		new_move->j = j;
	}

	// Now new_move should be updated
	if (game->make_move(game->board, new_move, game->current_player) == -1) {
		free(new_move);
		return -1;
	}
//	if (game->won_game(game)) {
//		return 0;
//	}
	// update the tree according to the new move
	update_tree(game->tree, game->board, j, i, game->current_player == FIRST_PL_TURN ? game->first_player_depth : game->second_player_depth);

	free(new_move);
	return 0;
}

/**
 * Saves required parameters of the game in required format
 * to a file, in order to allow retrieving.
 *
 * @param file_num	Number of file to save game to
 * @param game		Game struct that should contain current state
 */
int save_game(int file_num, Game* game) {

	char path_to_save[MAX_STR_LEN];
	FILE *write_file;
	int i, j, valid = 1;

	if (file_num <= FILES_NUM) {
		sprintf(path_to_save, FILE_PATH, file_num);
		write_file = fopen(path_to_save, "w");
		if (write_file == NULL ) {
			printf("Error: Could not open saved game %s\n", path_to_save);
			return 0;
		}
		if (check_validity(fprintf(write_file, "%s", game->save_game_name)) &&
			check_validity(fprintf(write_file, "\n%d\n", game->current_player))) {

			for (i = 0; i < game->board->n && valid; i++) {
				for (j = 0; j < (game->board->m - 1) && valid; j++) {
					valid = check_validity(fprintf(write_file, "%d ", game->board->cells[i][j]));
				}
				valid = check_validity(fprintf(write_file, "%d\n", game->board->cells[i][j]));
			}
			if (valid) {
				fclose(write_file);
				return 1;
			}
		}
		fclose(write_file);
	}
	return 0;
}

/**
 * Reads the file according to required format and
 * saves each fo the paremeters in the game struct.
 *
 * @param file_num	Number of file to load game from
 * @return	Game struct with state as read from file
 */
Game* load_game(int file_num) {

	int i, j, valid = 1;
	char path_to_read[MAX_STR_LEN];
	FILE *read_file;
	char game_name[MAX_STR_LEN];
	Game* loaded_game;

	sprintf(path_to_read, FILE_PATH, file_num);
	read_file = fopen(path_to_read, "r");
	if (read_file == NULL ) {
		printf("Error: Could not open saved game %s\n", path_to_read);
		return NULL;
	}
	if (check_validity(fscanf(read_file, "%s\n", game_name))) {
		// Create game according to name
		loaded_game = check_game(game_name);
		// Reading which player's turn
		if (check_validity(fscanf(read_file, "%d\n", &(loaded_game->current_player)))) {
			if ((loaded_game->current_player == FIRST_PL_TURN) || (loaded_game->current_player == SECOND_PL_TURN)) {
				// Reading board cells, according to size determined by game creation
				for (i = 0; i < loaded_game->board->n && valid; i++) {
					for (j = 0; j < (loaded_game->board->m - 1) && valid; j++) {
						valid = check_validity(fscanf(read_file, "%d ", &(loaded_game->board->cells[i][j])));
					}
					// Last one will have line break
					valid = check_validity(fscanf(read_file, "%d\n", &(loaded_game->board->cells[i][j])));
				}
				if (valid) {
					fclose(read_file);
					return loaded_game;
				}
			}
		}
	}
	fclose(read_file);
	return NULL;
}

/**
 * Create suitable game according to given name
 */
Game* check_game(char game_name[MAX_STR_LEN]) {
	if (strcmp(game_name, CONNECT4_NAME) == 0) {
		return connect4_new_game();
	}
	if (strcmp(game_name, REVERSI_NAME) == 0) {
		return reversi_new_game();
	}
	if (strcmp(game_name, TTT_NAME) == 0) {
		return ttt_new_game();
	}
	return NULL;
}

/**
 * If rc < 0, means there was an IO error,
 * either reading or writing.
 * Outputs suitable message.
 */
int check_validity(int rc) {
	if (rc <= 0) {
		printf("Error: Game file not in expected format\n");
		return 0;
	}
	return 1;
}

int file_exists(int file_num) {
	char path_to_read[MAX_STR_LEN];
	FILE *read_file;

	sprintf(path_to_read, FILE_PATH, file_num);
	read_file = fopen(path_to_read, "r");
	if (read_file == NULL ) {
		return 0;
	}
	fclose(read_file);
	return 1;
}
