/*
 * playit_conf.h
 *
 *  Created on: Mar 1, 2014
 *      Author: shir
 */

#ifndef PLAYIT_CONF_H_
#define PLAYIT_CONF_H_

#define IMGS_PATH		"../resources/"

// Main menu
#define PLAYIT_IMG		"PlayIt.bmp"
#define NEW_GAME_IMG	"NewGame.bmp"
#define LOAD_GAME_IMG	"LoadGame.bmp"
#define QUIT_IMG		"Quit.bmp"
#define BG_IMG			"Background.bmp"
#define CANCEL_IMG		"Cancel.bmp"
#define CANCEL_HAN		on_cancel

// Player selection menu
#define P_VS_P_IMG		"PLvsPL.bmp"
#define P_VS_A_IMG		"PLvsAI.bmp"
#define A_VS_A_IMG		"AIvsAI.bmp"
#define A_VS_P_IMG		"AIvsPL.bmp"
#define AI_PLAYING		1
#define PL_PLAYING		0
#define SELECT_P_IMG	"SelectPlayer.bmp"
#define NUM_PLAY_TYPES	4

// Game arena menu
#define SAVE_GAME_IMG	"SaveGame.bmp"
#define DIFF1_IMG		"Difficulty1.bmp"
#define DIFF2_IMG		"Difficulty2.bmp"
#define RESTART_GAME_IMG "/RestartGame.bmp"
#define MAIN_MENU_IMG	"MainMenu.bmp"
#define NUM_GAMES		3

// Game selection
#define SELECT_G_IMG	"SelectGame.bmp"
#define REVERSI_IMG		"Reversi.bmp"
#define REVERSI_HAN		on_select_reversi
#define TIC_TAC_TOE_IMG	"TicTacToe.bmp"
#define TIC_TAC_TOE_HAN	on_select_tictactoe
#define CONNECT4_IMG	"Connect4.bmp"
#define CONNECT4_HAN	on_select_connect4

// Reversi tiles
#define RB_IMG			"rB.bmp"
#define RW_IMG			"rW.bmp"
#define RN_IMG			"rN.bmp"

// Tic tac toe tiles
#define TTTN_IMG		"tttN.bmp"
#define TTTO_IMG		"tttO.bmp"
#define TTTX_IMG		"tttX.bmp"

// Connect4 tiles
#define C4N_IMG			"c4N.bmp"
#define C4P1_IMG		"c4P1.bmp"
#define C4P2_IMG		"c4P2.bmp"

// Size parameters
#define WIN_W 640
#define WIN_H 480
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
#define BOARD_PANEL_W	WIN_W - BUT_W - 20
#define MAX_STR_LEN		80

// Game saving \ loading
#define FILE_NAME		"Game File"
#define FILES_NUM		5
#define FILE_SELECT		"SelectFile.bmp"
#define FILE_PATH		"../files/game_file_%d.txt"
#define TTT_NAME		"Tic Tac Toe";
#define	CONNECT_NAME	"Connect 4";
#define REVERSI_NAME	"Reversi";

// General label
#define TEXT_BG			"Plain.bmp"
#define TEXT_FONT		"/usr/share/fonts/truetype/freefont/FreeMonoBoldOblique.ttf"

#endif /* PLAYIT_CONF_H_ */
