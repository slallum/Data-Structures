/*
 * playit_conf.h
 *
 *  Created on: Mar 1, 2014
 *      Author: shir
 */

#ifndef PLAYIT_CONF_H_
#define PLAYIT_CONF_H_

#include <stdlib.h>
#include <stdio.h>

#define IMGS_PATH		"./resources/"

// Main menu
#define PLAYIT_IMG		"PlayIt.bmp"
#define NEW_GAME_IMG	"New Game"
#define LOAD_GAME_IMG	"Load Game"
#define QUIT_IMG		"Quit"
#define BG_IMG			"Background.bmp"
#define CANCEL_IMG		"Cancel.bmp"
#define CANCEL_HAN		on_cancel

// Player selection menu
#define P_VS_P_IMG		"Pl vs. Pl"
#define P_VS_A_IMG		"Pl vs. AI"
#define A_VS_A_IMG		"AI vs. AI"
#define A_VS_P_IMG		"AI vs. Pl"
#define AI_PLAYING		1
#define PL_PLAYING		0
#define NO_PLAYER		-1
#define FIRST_PL_TURN	1
#define SECOND_PL_TURN	-1
#define WINNING_TURN	2
#define SELECT_P_IMG	"SelectPlayer.bmp"
#define NUM_PLAY_TYPES	4

// Game arena menu
#define SAVE_GAME_IMG	"Save Game"
#define RESUME_GAME_IMG	"Resume"
#define RESTART_GAME_IMG "Restart Game"
#define MAIN_MENU_IMG	"Main Menu"
#define NUM_GAMES		3

// Game arena info
#define PLAYER1_IMG		"PlayerI.bmp"
#define PLAYER1_H_IMG	"PlayerIH.bmp"
#define PLAYER2_IMG		"PlayerII.bmp"
#define PLAYER2_H_IMG	"PlayerIIH.bmp"
#define TROPHY_IMG		"Trophy.bmp"
#define TROPHY_TILE_IMG	"TrophyTile.bmp"
#define NO_IMG			"Empty.bmp"

// Game selection
#define SELECT_G_IMG	"SelectGame.bmp"
#define REVERSI_IMG		"Reversi"
#define REVERSI_HAN		on_select_reversi
#define TIC_TAC_TOE_IMG	"Tic-Tac-Toe"
#define TIC_TAC_TOE_HAN	on_select_tictactoe
#define CONNECT4_IMG	"Connect 4"
#define CONNECT4_HAN	on_select_connect4

// Reversi
#define RB_IMG			"rB.bmp"
#define RW_IMG			"rW.bmp"
#define RN_IMG			"rN.bmp"
#define REVERSI_BOARD_N	8
#define REVERSI_BOARD_M	8

// Tic tac toe
#define TTTN_IMG		"tttN.bmp"
#define TTTO_IMG		"tttO.bmp"
#define TTTX_IMG		"tttX.bmp"
#define TTT_BOARD_N		3
#define TTT_BOARD_M		3

// Connect4
#define C4N_IMG			"c4N.bmp"
#define C4P1_IMG		"c4P1.bmp"
#define C4P2_IMG		"c4P2.bmp"
#define C4_BOARD_N		6
#define C4_BOARD_M		7

// Size parameters
#define WIN_W			800
#define WIN_H			600
#define HEADING			"Play it!"
#define MARGIN_H		30
#define LOGO_DIM		150
#define TITLE_H			60
#define TITLE_W			300
#define BUT_H			50
#define	BUT_W			200
#define TILE_W			50
#define TILE_H			50
#define TILE_SPACE		10
#define BOARD_PANEL_W	WIN_W - BUT_W - 10
#define BOARD_PANEL_H	WIN_H - TITLE_H * 2
#define INFO_PANEL_X	20
#define INFO_PANEL_Y	5
#define MAX_STR_LEN		80

// Game saving \ loading
#define FILE_NAME		"Game"
#define FILES_NUM		5
#define FILE_SELECT		"SelectFile.bmp"
#define FILE_PATH		"./files/game_file_%d.txt"
#define TTT_NAME		"Tic-tac-toe"
#define	CONNECT4_NAME	"Connect4"
#define REVERSI_NAME	"Reversi"

// Tree
#define EXTREME_VALUE 100000

// General label
#define TEXT_BG			"Plain.bmp"
#define TEXT_CHAR_BG	"charPlain.bmp"
#define TEXT_SIZE		28
#define TEXT_FONT		"/usr/share/fonts/truetype/freefont/FreeMonoBoldOblique.ttf"

#endif /* PLAYIT_CONF_H_ */
