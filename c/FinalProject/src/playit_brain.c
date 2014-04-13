/*
 * playit_brain.c
 *
 *  Created on: Mar 13, 2014
 *      Author: shir
 */

#include "playit_brain.h"


int switch_player(Game* game) {
	if (no_moves(game, game->is_first_players_turn * SECOND_PL_TURN) == 0) {
		game->is_first_players_turn = game->is_first_players_turn * (SECOND_PL_TURN);
	}
	if ((game->is_first_players_turn == FIRST_PL_TURN) && (game->first_player_ai == AI_PLAYING)) {
		return 1;
	}
	if ((game->is_first_players_turn == SECOND_PL_TURN) && (game->second_player_ai == AI_PLAYING)) {
		return 1;
	}
	return 0;
}

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
int handle_move(Game* game, int i, int j) {
	Move* new_move = (Move*) malloc(sizeof(Move));
	new_move->i = i;
	new_move->j = j;
	// Now new_move should be updated
	if (game->make_move(game->board, new_move, game->is_first_players_turn) == -1) {
		free(new_move);
		return -1;
	}
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
	int i, j;

	if (file_num <= FILES_NUM) {
		sprintf(path_to_save, FILE_PATH, file_num);
		write_file = fopen(path_to_save, "w");
		if (write_file == NULL ) {
			printf("Error: Could not open saved game %s\n", path_to_save);
			return 0;
		}
		check_validity(fprintf(write_file, "%s", game->save_game_name));
		check_validity(fprintf(write_file, "\n%d\n", game->is_first_players_turn));
		for (i = 0; i < game->board->n; i++) {
			for (j = 0; j < (game->board->m - 1); j++) {
				check_validity(fprintf(write_file, "%d ", game->board->cells[i][j]));
			}
			check_validity(fprintf(write_file, "%d\n", game->board->cells[i][j]));
		}
		fclose(write_file);
	}
	return 1;
}

/**
 * Reads the file according to required format and
 * saves each fo the paremeters in the game struct.
 *
 * @param file_num	Number of file to load game from
 * @return	Game struct with state as read from file
 */
Game* load_game(int file_num) {

	int i, j;
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
	check_validity(fscanf(read_file, "%s\n", game_name));
	// Create game according to name
	if (strcmp(game_name, CONNECT4_NAME) == 0) {
		loaded_game = connect4_new_game();
	}
	if (strcmp(game_name, REVERSI_NAME) == 0) {
		loaded_game = reversi_new_game();
	}
	if (strcmp(game_name, TTT_NAME) == 0) {
		loaded_game = ttt_new_game();
	}
	// Reading which player's turn
	check_validity(fscanf(read_file, "%d\n", &(loaded_game->is_first_players_turn)));
	// Reading board cells, according to size determined by game creation
	for (i = 0; i < loaded_game->board->n; i++) {
		for (j = 0; j < (loaded_game->board->m - 1); j++) {
			check_validity(fscanf(read_file, "%d ", &(loaded_game->board->cells[i][j])));
		}
		// Last one will have line break
		check_validity(fscanf(read_file, "%d\n", &(loaded_game->board->cells[i][j])));
	}
	fclose(read_file);
	return loaded_game;
}

void check_validity(int rc) {
	if (rc <= 0) {
		printf("Error: Game file not in expected format\n");
	}
}
