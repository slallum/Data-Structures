<<<<<<< HEAD

C_FLAGS = -std=c99 -Wall -g -pedantic-errors -lm -lSDL_ttf
O_FILES = playit.o gui_framework.o playit_gui.o playit_manager.o playit_brain.o connect4_brain.o game_framework.o board.o tree.o

=======
C_FLAGS = -std=c99 -Wall -g -pedantic-errors -lm -lSDL_ttf
O_FILES = playit.o gui_framework.o playit_gui.o playit_manager.o playit_brain.o connect4_brain.o game_framework.o
>>>>>>> c3a9346554a154b2540d3a0a01469152d10b975e

all: PlayIt
clean:
	-rm $(O_FILES) PlayIt

PlayIt: $(O_FILES)
	gcc -o PlayIt $(O_FILES) $(C_FLAGS) `sdl-config --libs`
	
playit.o:		playit.c playit.h gui_framework.h playit_gui.h
	gcc $(C_FLAGS) -c playit.c -o playit.o `sdl-config --cflags`
	
board.o:			board.c board.h
	gcc $(C_FLAGS) -c board.c -o board.o `sdl-config --cflags`

tree.o:				tree.c tree.h board.h
	gcc $(C_FLAGS) -c tree.c -o tree.o `sdl-config --cflags`

gui_framework.o:	gui_framework.c gui_framework.h
	gcc $(C_FLAGS) -c gui_framework.c `sdl-config --cflags`

game_framework.o:	game_framework.c game_framework.h tree.h board.h
	gcc $(C_FLAGS) -c game_framework.c `sdl-config --cflags`
	
playit_gui.o:		playit_gui.c playit_gui.h playit_conf.h playit_manager.h gui_framework.h game_framework.h
	gcc $(C_FLAGS) -c playit_gui.c `sdl-config --cflags`

playit_manager.o:	playit_manager.c playit_manager.h playit_gui.h playit_brain.h playit_conf.h
	gcc $(C_FLAGS) -c playit_manager.c `sdl-config --cflags`

<<<<<<< HEAD
connect4_brain.o:   connect4_brain.c connect4_brain.h game_framework.h board.h tree.h	
=======
connect4_brain.o:   	connect4_brain.c connect4_brain.h game_framework.h
>>>>>>> c3a9346554a154b2540d3a0a01469152d10b975e
	gcc $(C_FLAGS) -c connect4_brain.c `sdl-config --cflags`

playit_brain.o:		playit_brain.c playit_brain.h playit_conf.h connect4_brain.h
	gcc $(C_FLAGS) -c playit_brain.c `sdl-config --cflags`


