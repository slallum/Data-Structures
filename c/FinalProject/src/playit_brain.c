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
	}
	fprintf(write_file, "%s", game_name);
	fprintf(write_file, "\n%d\n", game->is_first_players_turn);
	for (i = 0; i < game->board->n; i++) {
		for (j = 0; j < game->board->m - 1; j++) {
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

	char path_to_read[MAX_STR_LEN], c, *current_line, *game_name, *matrix;
	FILE *read_file;

	Game* loaded_game = (Game*) malloc(sizeof(Game));
	sprintf(path_to_read, FILE_PATH, file_num);
	read_file = fopen(path_to_read, "r");
	if (read_file == NULL ) {
		printf("Error: Could not open saved game %s\n", path_to_read);
		return NULL ;
	}
//	if (fscanf(read_file, "%s\n%d\n%s", game_name, &(loaded_game->is_first_players_turn),
//			matrix) < 0) {
//		printf("Error: Wring format for saved game %s\n", path_to_read);
//		free(loaded_game);
//		return NULL;
//	}
	c = fgetc(read_file);
	while (!feof(read_file)) {
		while (c != '\n') {

		}
	}
	printf("%s\n", game_name);
	printf("%d\n", loaded_game->is_first_players_turn);
	fclose(read_file);
	return loaded_game;
}
