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
int save_game(int file_num, Game* game, char* game_name) {

	char path_to_save[MAX_STR_LEN];
	FILE *write_file;
	int i, j;

	sprintf(path_to_save, FILE_PATH, file_num);
	write_file = fopen(path_to_save, "w");
	if (write_file == NULL ) {
		printf("Error: Could not open saved game %s\n", path_to_save);
		return 0;
	}
	fprintf(write_file, "%s", game_name);
	fprintf(write_file, "\n%d\n", game->is_first_players_turn);
	for (i = 0; i < game->board->n; i++) {
		for (j = 0; j < (game->board->m - 1); j++) {
			fprintf(write_file, "%d ", game->board->cells[i][j]);
		}
		fprintf(write_file, "%d\n", game->board->cells[i][j]);
	}
	fclose(write_file);
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
	if (fscanf(read_file, "%s\n", game_name) < 0) {
		printf("Error: Missing saved game name %s\n", path_to_read);
		return NULL;
	}
	// Create game according to name
	if (strcmp(game_name, CONNECT4_NAME) == 0) {
		loaded_game = connect4_new_game();
	}
	if (strcmp(game_name, REVERSI_NAME) == 0) {
		// TODO
	}
	if (strcmp(game_name, TTT_NAME) == 0) {
		// TODO
	}
	if (fscanf(read_file, "%d\n", &(loaded_game->is_first_players_turn)) < 0) {
		printf("Error: Missing first player signification in %s\n", path_to_read);
		return NULL;
	}
	for (i = 0; i < loaded_game->board->n; i++) {
		for (j = 0; j < (loaded_game->board->m - 1); j++) {
			if (fscanf(read_file, "%d ", &(loaded_game->board->cells[i][j])) < 0) {
				printf("Error: Missing cell in %s\n", path_to_read);
				return NULL;
			}
		}
		if (fscanf(read_file, "%d\n", &(loaded_game->board->cells[i][j])) < 0) {
			printf("Error: Missing cell in %s\n", path_to_read);
			return NULL;
		}
	}

	fclose(read_file);
	return loaded_game;
}
