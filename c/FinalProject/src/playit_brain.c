/*
 * playit_brain.c
 *
 *  Created on: Mar 13, 2014
 *      Author: shir
 */

#include "playit_brain.h"



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
		if (check_validity(sprintf(path_to_save, FILE_PATH, file_num))) {
			write_file = fopen(path_to_save, "w");
			if (write_file == NULL ) {
				printf("ERROR: Could not open saved game %s\n", path_to_save);
				return 0;
			}
			if (check_validity(fprintf(write_file, "%s", game->save_game_name)) &&
				check_validity(fprintf(write_file, "\n%d\n", game->current_player))) {

				for (i = 0; i < game->board->n && valid; i++) {
					for (j = 0; j < (game->board->m - 1) && valid; j++) {
						if (game->board->cells[i][j] == WINNING_TURN) {
							valid = check_validity(fprintf(write_file, "%d ", game->current_player));
						} else {
							valid = check_validity(fprintf(write_file, "%d ", game->board->cells[i][j]));
						}
					}
					if (game->board->cells[i][j] == WINNING_TURN) {
						valid = check_validity(fprintf(write_file, "%d\n", game->current_player));
					} else {
						valid = check_validity(fprintf(write_file, "%d\n", game->board->cells[i][j]));
					}
				}
				if (valid) {
					fclose(write_file);
					return 1;
				}
			}
			fclose(write_file);
		}
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

	if (check_validity(sprintf(path_to_read, FILE_PATH, file_num))) {
		read_file = fopen(path_to_read, "r");
		if (read_file == NULL ) {
			printf("ERROR: Could not open saved game %s\n", path_to_read);
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
						loaded_game->won_game(loaded_game);
						return loaded_game;
					}
				}
			}
		}
		fclose(read_file);
	}
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
		printf("ERROR: Game file not in expected format\n");
		return 0;
	}
	return 1;
}

/**
 * Returns whether the game file number file_num exists
 */
int file_exists(int file_num) {
	char path_to_read[MAX_STR_LEN];
	FILE *read_file;

	if (check_validity(sprintf(path_to_read, FILE_PATH, file_num))) {
		read_file = fopen(path_to_read, "r");
		if (read_file == NULL ) {
			return 0;
		}
		fclose(read_file);
		return 1;
	}
	return 0;
}
