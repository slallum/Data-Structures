/*
 * playit_conf.h
 *
 *  Created on: Mar 1, 2014
 *      Author: shir
 */

#ifndef PLAYIT_CONF_H_
#define PLAYIT_CONF_H_

#define PLAYIT_IMG		"../resources/PlayIt.bmp"
#define NEW_GAME_IMG	"../resources/NewGame.bmp"
#define LOAD_GAME_IMG	"../resources/LoadGame.bmp"
#define QUIT_IMG		"../resources/Quit.bmp"
#define BG_IMG			"../resources/Background.bmp"
#define CANCEL_IMG		"../resources/Cancel.bmp"
#define CANCEL_HAN		on_cancel

#define P_VS_P_IMG		"../resources/PLvsPL.bmp"
#define P_VS_P_HAN		on_select_pl_pl
#define P_VS_A_IMG		"../resources/PLvsAI.bmp"
#define P_VS_A_HAN		on_select_pl_ai
#define A_VS_A_IMG		"../resources/AIvsAI.bmp"
#define A_VS_A_HAN		on_select_ai_ai
#define A_VS_P_IMG		"../resources/AIvsPL.bmp"
#define A_VS_P_HAN		on_select_ai_pl
#define SELECT_P_IMG	"../resources/SelectPlayer.bmp"
#define NUM_PLAY_TYPES	4

#define SAVE_GAME_IMG	"../resources/SaveGame.bmp"
#define DIFF1_IMG		"../resources/Difficulty1.bmp"
#define DIFF2_IMG		"../resources/Difficulty2.bmp"
#define RESTART_GAME_IMG "../resources/RestartGame.bmp"
#define MAIN_MENU_IMG	"../resources/MainMenu.bmp"
#define NUM_GAMES		3

#define SELECT_G_IMG	"../resources/SelectGame.bmp"
#define REVERSI_IMG		"../resources/Reversi.bmp"
#define REVERSI_HAN		on_select_reversi
#define RB_IMG			"../resources/rB.bmp"
#define RW_IMG			"../resources/rW.bmp"
#define RN_IMG			"../resources/rN.bmp"

#define TIC_TAC_TOE_IMG	"../resources/TicTacToe.bmp"
#define TIC_TAC_TOE_HAN	on_select_tictactoe
#define TTTN_IMG		"../resources/tttN.bmp"
#define TTTO_IMG		"../resources/tttO.bmp"
#define TTTX_IMG		"../resources/tttX.bmp"

#define CONNECT4_IMG	"../resources/Connect4.bmp"
#define CONNECT4_HAN	on_select_connect4
#define C4N_IMG			"../resources/c4N.bmp"
#define C4P1_IMG		"../resources/c4P1.bmp"
#define C4P2_IMG		"../resources/c4P2.bmp"

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

#endif /* PLAYIT_CONF_H_ */
